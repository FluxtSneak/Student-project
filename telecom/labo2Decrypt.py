import sys
import os

# read input and key
crypted_file = open(os.path.join(os.getcwd(), sys.argv[1]), mode="r+b")
key_file=open(os.path.join(os.getcwd(), sys.argv[2]), mode="r+b")

# file to list
crypted = list(crypted_file.read())
crypted_file.close()
#key to list
k = list(key_file.read())
key_file.close()

def decrypt(input,key):
    output=bytes(0)
    for i in range(len(input)):
        output+=(key[i]^input[i]).to_bytes(1,'big')

    return output

decrypted=decrypt(crypted,k)
decrypted_file = open(os.path.join(os.getcwd(), 'decrypted.txt'), 'wb')
decrypted_file.write(decrypted)
decrypted_file.close()
