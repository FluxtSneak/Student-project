import collections
import math
import sys
import os



#a
#open input file and put it's content to tab
input_file=open(os.path.join(os.getcwd(), sys.argv[1]), "r", encoding="UTF-8")
tab=list(input_file.read())
input_file.close()

#open output file
output_file1=open(os.path.join(os.getcwd(), "out1.txt"), "w", encoding="UTF-8")

#sort data and write them in output file
tab = sorted(tab)
for item in tab:
        output_file1.write(item)
output_file1.close()


#b
#open output file
output_file2=open(os.path.join(os.getcwd(), "out2.txt"), "w", encoding="UTF-8")

#create dictionary [char,occurences]
dic ={}
for x in tab :
    if x in dic :
        dic[x] +=1
    else :
        dic[x] =1

#sort by values
dic = sorted(dic.items(), key=lambda x: x[1],reverse=True)


#entropy
h=0

print("question b: \n")
#write 
for item in dic:
        output_file2.write(item[0])

        prob=item[1]/len(tab)

        print("0x"+str(ord(item[0]))+" "+str(prob))

        h+=prob*(-math.log2(prob))

#decision's quantity
d=math.ceil(math.log2(len(dic)))
#redundance
r=d-h
#compresion rate
t=(d-h)/h

print("\nquestion c: \n")
print("entropie = "+str(h))
print("quantité de décision = "+str(d))
print("redondance = "+str(r))
print("taux max de compression = "+str(t))

