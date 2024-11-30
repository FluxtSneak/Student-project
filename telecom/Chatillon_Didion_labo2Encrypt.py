import sys
import os
import random
# a
print("a: la taille de la clé doit etre la meme que la taille du message")
# b
print("b.a :", 17 ^ 5)
print("b.b :", 17 ^ 20)
print("b.c :", 5 ^ 20)
# c
print("c: on observe que l'oppération est réversible !")

# read input file
input_file = open(os.path.join(os.getcwd(), sys.argv[1]), mode="r+b")

# file to list
li = list(input_file.read())
input_file.close()

#generate key
random.seed(a="Didion Chatillon")
r=random.randbytes(len(li))
k=list(r)

key_file = open(os.path.join(os.getcwd(), 'key.bin'), 'wb')
key_file.write(r)
key_file.close()

def encrypt(input,key):
    output=bytes(0)
    for i in range(len(input)):
        output+=(key[i]^input[i]).to_bytes(1,'big')

    return output

encrypted=encrypt(li,k)
#write to file
crypted_file = open(os.path.join(os.getcwd(), 'crypted.bin'), 'wb')
crypted_file.write(encrypted)
crypted_file.close()

#bonus
#sources: cours de T. Maliki
print("B.1: on peut transmetre la seed, permettant de regener la clé")
print("B.2: en principe oui, la cryptoanalyse est inefficace avec un seul message, seul la brute force reste possible, tout depend de la longueur de la clé.")
print("B.3: c'est n'est pas du 'vrai aléatoire': si on trouve la seed on peut regener la clé ! 2 alternatives : le bruit therminque et le déplacement des électrons")
