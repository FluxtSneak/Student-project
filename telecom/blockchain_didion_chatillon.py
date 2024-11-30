import hashlib
import sys
import os
import shutil
import time

#nombre de 0 au début du hash
nonce_len = 13

def byteToBits(bytesA,nbBits):
    bits = ''
    for byte in bytesA: 
        bits+=bin(byte)[2:].zfill(8)
        if(len(bits)>=nbBits):
            break
    return bits[:nbBits]


def bytesNeeded(val):
    if (val < 0x10000):
        if (val < 0x100):
            return 8
        return 16
    else:
        if (val < 0x100000000):
            return 32
        else:
            return 64

def compute_nonce(val):
    start = time.time()
    nonce = 0
    new_content=val
    while(True):
        new_content = val+nonce.to_bytes(bytesNeeded(nonce), 'big')
        block_hash = hashlib.sha256(new_content).digest()
        if(byteToBits(block_hash,nonce_len) == ''.zfill(nonce_len)):
            break
        nonce += 1

    end = time.time()
    print(nonce_len,"zeros computed in:",end-start, 'sec')
    print("nonce:", nonce)
    print("hash:",byteToBits(block_hash,256))
    return nonce.to_bytes(bytesNeeded(nonce),'big')

def main():
    
    # create or overwrite dir
    dir = os.path.join(os.getcwd(), 'blockchain')
    if(os.path.exists(dir)):
        shutil.rmtree(dir)
    os.mkdir(dir)
    
    block_index = 0
    block_hash=int(0).to_bytes(32, 'big')

    while(block_index < 256):
        if(block_index==0):
            block0 = open(os.path.join(os.getcwd(), sys.argv[1]), mode="rb")
            content = block0.read()
            block0.close()
        else:

            file_name = input("enter next block's name\n")
            while(not os.path.isfile(file_name)):
                file_name = input("invalid filename, enter correct block's name\n")

            input_file = open(os.path.join(os.getcwd(), file_name), mode="rb")
            content = input_file.read()
            input_file.close()

        content = block_index.to_bytes(1, 'big')+ block_hash+content

        nonce=compute_nonce(content)
        content+=nonce

        block_file = open(os.path.join(dir, 'block'+str(block_index)+'.bin'), mode="wb")
        block_file.write(content)
        block_file.close()

        block_hash = hashlib.sha256(content).digest()
        block_index += 1

main()