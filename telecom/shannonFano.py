import sys
import math
import os
from operator import itemgetter


# read input file
input_file = open(os.path.join(
    os.getcwd(), sys.argv[1]), "r", encoding="UTF-8")

# file to list
li = list(input_file.read())
input_file.close()

# create dict [char - nb of occurence]
dProb = {}
# create dict [char - shannon fano code]
dSF = {}

for x in li:
    if x in dProb:
        dProb[x] += 1
    else:
        dProb[x] = 1


#entropie
h=0
for x in dProb:
    prob=dProb[x]/len(li)
    h+=prob*(-math.log2(prob))
  

def shannonFano(dOcc, code):
    e1 = {}
    e2 = {}
    if len(dOcc) == 1:  # end of recusion
        dSF[dOcc.popitem()[0]] = code  # add value to dico SF
        return 0

    values = [pair[1] for pair in sorted(dOcc.items(), key=itemgetter(1))]#list of dico values
    i = 0
    while(sum(values[0:i]) <= sum(values[i:])):#find i where e1>e2
        i += 1

    s = 0
    for pair in sorted(dOcc.items(), key=itemgetter(1)):#add kvp to dico until i[
        s += pair[1]
        if(s > sum(values[0:i-1])):
            e1[pair[0]] = +pair[1]
        else:
            e2[pair[0]] = +pair[1]

    #recursion
    shannonFano(e1, code+"0")
    shannonFano(e2, code+"1")


shannonFano(dProb, "")


lm=0
print("question a: \n")
for pair in sorted(dSF.items(),key=lambda x:len(x[1])) :
    print (pair[0]+" 0x"+str(ord(pair[0]))+": "+pair[1])
    lm+=len(pair[1])

lm/=len(dSF)

print("\nquestion b: \n")
print("Lm= "+str(lm))
print("h = "+str(h))
print("h<Lm donc on peut encore optimiser le codage ex: avec un autre type de codage \n")


code=""

#encode text
for char in li:
    code+=dSF[char] 

while len(code)%8!=0: #make sure it's a multiple of 8
    code+="0"

#write bin file
if len(sys.argv)!=3:
    print("usage : shannonFano_didion_chatillon.py input.txt out.bin")
    exit(1)

output_file = open(sys.argv[2],"wb")
b=int(code, 2).to_bytes(int(len(code)/8), 'big')

output_file.write(b)
output_file.close()

