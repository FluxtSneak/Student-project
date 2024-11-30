import collections
import math
import sys
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
# create dict [char - huffman code]
dHuf = {}

for x in li:
    if x in dProb:
        dProb[x] += 1
    else:
        dProb[x] = 1

    if x not in dHuf:
        dHuf[x] = ""

# entropie
h = 0
for x in dProb:
    prob = dProb[x]/len(li)
    h += prob*(-math.log2(prob))


# huffman
while len(dProb) > 1:
    # s2 = 2 smallest values
    s2 = sorted(dProb.items(), key=itemgetter(1))[:2]

    key1 = s2[0][0]
    val1 = s2[0][1]

    key2 = s2[1][0]
    val2 = s2[1][1]

    # merge the 2 values
    dProb.pop(key1)
    dProb.pop(key2)
    # into a new one
    dProb[key1+key2] = val1+val2

    # encode
    for i in key1:
        dHuf[i] += "0"
    for j in key2:
        dHuf[j] += "1"


lm = 0
print("question a: \n")
for pair in sorted(dHuf.items(), key=lambda x: len(x[1])):
    print("0x"+str(ord(pair[0]))+": "+pair[1])
    lm += len(pair[1])

lm /= len(dHuf)

print("\nquestion b: \n")
print("Lm= "+str(lm))
print("h = "+str(h))
print("h<Lm donc on peut encore optimiser le codage !\n")
print("question d: \n")
print("pour decoder le fichier .bin il faudrait y inclure la table de conversion")

hufman = ""

# encode text
for char in li:
    hufman += dHuf[char]

# ajoute un padding de 0 pour la convertion en bytes et les comptes
cpt = 0
while len(hufman) % 8 != 0:  # make sure it's a multiple of 8
    hufman += "0"
    cpt += 1
zeros = '{0:08b}'.format(cpt)
# write bin file
output_file = open(sys.argv[2], "wb")
b = int(hufman, 2).to_bytes(int(len(hufman)/8), 'big')
b += int(zeros, 2).to_bytes(1, 'big')
output_file.write(b)
output_file.close()
