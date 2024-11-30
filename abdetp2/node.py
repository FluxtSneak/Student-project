import sys
import socket
import argparse
import yaml
import threading
from threading import Thread
import pickle
import os

#Classes
class Node:
    def __init__(self, ide, addresse, neighb,ini):
        self.id=ide
        self.name="node"+str(ide)
        self.address=addresse
        self.neigh=neighb
        self.init=ini

class Message:
    def __init__(self,id):
        self.id=id
        self.action =action
        self.proactif=proactif

class MySet:
    def __init__(self,set_):
        self.set_lst=set_

#Declarations
action=None
count=0 #=t in algo slides
neigh_count=list() #used to count till we have received all set from neighbours
number_nodes=6
port=None
node=None
temp=list()
future_set=list() #a list of tuple (sended_by, set_sended)
routing_table=list()# content of the list = nb_hops to get there, which neighbor to send the data, final destination

#Manualy init routing table to all max
routing_table.append([number_nodes,None,'10.0.0.1'])
routing_table.append([number_nodes,None,'10.0.0.2'])
routing_table.append([number_nodes,None,'10.0.0.3'])
routing_table.append([number_nodes,None,'10.0.0.4'])
routing_table.append([number_nodes,None,'10.0.0.5'])
routing_table.append([number_nodes,None,'10.0.0.6'])

#mutexes for global variables accessed by multiples threads 
mutexN = threading.Lock()
mutexC = threading.Lock()
mutexF = threading.Lock()
mutexR = threading.Lock()


#Functions

#load node datas from yaml file
def get_node_datas(name):
    with open(name) as f:
        docs = yaml.load(f, Loader=yaml.FullLoader)
    return docs

#init node with yaml datas
def init_node(datas,init):
    id=datas["id"]
    address=datas["address"]
    neigh=list()
    for n in datas["neighbours"]:
        neigh.append((n["id"],n["address"]))
    node=Node(id,address,neigh,init)
    return node

def update_routing_table(hop,neigh_ip,ip_to_reach):
    global routing_table
    for element in routing_table:
        if element[2]==ip_to_reach:
            element[0]=hop
            element[1]=neigh_ip

def get_routing_table_element(ip_to_reach):
    for element in routing_table:

        if str(element[2])==str(ip_to_reach):
            return element

def send_data(target, data):
    data_s=pickle.dumps(data)
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((target, 9999))
    sock.send(data_s)
    sock.close()

def send_to_all_neigh(data):
    global node
    for nei in node.neigh:
        send_data(nei[1], data)

#returns True if the future set already contains a set from this neigh
def already_contains(sender_ip):
    global future_set
    for set_ in future_set:
        if set_[0]==sender_ip:
            return True
    return False

#increase the counter of set received from a neigh
def increase_neigh_count(neigh_ip):
    global neigh_count
    for neigh in neigh_count:
        if neigh[0]==neigh_ip:
            neigh[1]=neigh[1]+1

#return the total of set currently held by the node (in future set and temp)
def neigh_sum():
    global neigh_count
    sum=0
    for neigh in neigh_count:
        sum=sum+neigh[1]
    return sum

#returns true if all neigh sent at least 1 message
def check_neigh_count():
    global neigh_count
    for neigh in neigh_count:
        if neigh[1]<1:
            return False
    return True

#decrease the counter of set received by all neigh by 1 (done after sending a full set to neighbs)
def decrease_all_neigh():
    global neigh_count
    for neigh in neigh_count:
        neigh[1]=neigh[1]-1

def handle_data(c):
    global count
    global action
    global node
    global neigh_count
    global number_nodes
    global future_set
    global routing_table
    global temp

    data=pickle.loads(c.recv(4096))
    sender_ip = c.getpeername()[0]
    mutexC.acquire()
    mutexN.acquire()
    if neigh_sum()==0:
        mutexF.acquire()
        future_set=list()
        mutexF.release()
        #first time a message is received, send set 0 to neighb
        if count==0 and action =='WAIT':
            send_to_all_neigh(MySet([node.address]))
    increase_neigh_count(sender_ip)
    mutexN.release()
    mutexC.release()

    mutexF.acquire()
    if already_contains(sender_ip):
        temp.append([sender_ip,data.set_lst])
    else:
        future_set.append([sender_ip,data.set_lst])        
    mutexF.release()

    mutexC.acquire()
    mutexN.acquire()
    if check_neigh_count(): #the new set of timing 'count' is full
        count=count+1
        decrease_all_neigh()
        #check for needed updates in the routing table
        for set_ in future_set:
            for node_ip in set_[1]:
                routing_table_element=get_routing_table_element(node_ip)
                if int(routing_table_element[0])>count:
                    mutexR.acquire()
                    update_routing_table(count, set_[0],node_ip)
                    mutexR.release()
        if count<number_nodes-1:
            #generate the new set to send
            datas=list()
            for set_ in future_set:
                for data in set_[1]:
                    datas.append(data)
            send_to_all_neigh(MySet(datas))
            #reset the future set
            future_set.clear()
            #transfert set in temp to future set
            for set_ in temp:
                if not already_contains(set_[0]):
                    future_set.append(set_)
                    temp.remove(set_)
        else:
            print("routing table :")
            print(routing_table)
    mutexN.release()
    mutexC.release()
    c.close()

def Main():
    if (len(sys.argv)<3):
        print("Missing argument\nusage : node.py num_port neighbour-x.yaml INIT/WAIT")
        exit()
    global node
    global routing_table
    global count
    global port
    global action
    global neigh_count
    #get info if need to init the algo
    action=str(sys.argv[3])
    port=str(sys.argv[1])
    datas=get_node_datas(str(sys.argv[2]))
    #init node
    node=init_node(datas,action)
    update_routing_table(0, node.address, node.address)
    for neigh in node.neigh:
        neigh_count.append([neigh[1],0])
    
    #open connection listner on 127.0.0.X
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((node.address, 9999))
    print("Serveur listening",node.address)
    s.listen(1)
    if action=='INIT':
        send_to_all_neigh(MySet([node.address]))
    #wait for client connection
    while True:
        # establish connection with client and start a thread to handle the com
        clientConnected, clientAddress = s.accept()
        print("Client :"+str(clientAddress)+" connected")
        thread = Thread(target=handle_data, args=(clientConnected,))
        thread.start()
    s.close()
    
if __name__ == "__main__":
    Main()