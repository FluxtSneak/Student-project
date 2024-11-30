def add_mod16(a, b):
    return str(bin((int(a, 2)+int(b, 2)) % 16))[2:].zfill(4)


def mult_mod17(a, b):
    return str(bin((int(a, 2)*int(b, 2)) % 17))[2:].zfill(4)

def inv_mult_mod17(A):
    if(int(A, 2)==0):
        return '0000'

    a = r = int(A, 2)
    b = 17

    x = [1, 0]
    y = [0, 1]
    i = 2

    while r != 0:
        r = a % b
        q = a//b
        a = b
        b = r
        x.append(x[i-2]-q*x[i-1])
        y.append(y[i-2]-q*y[i-1])
        i += 1

    return str(bin((x[len(x)-2])%17))[2:].zfill(4)


def inv_add_mod16(a):#inv add de 5= 16-5= 11 car 11+5%16=0
    if(int(a, 2)==0):
        return '0000'
    return str(bin(16-int(a, 2)))[2:].zfill(4)


def xor(a, b):
    return a ^ b


def encrypt_keys(key):
    if(len(key) % 4 != 0):
        print('error: length must be a multiple of 4 !')
        return

    subkeys = [[] for i in range(5)]
    for r in range(4):  # new round
        for i in range(8):
            if(r == 3 and i == 4):
                return subkeys
            if(len(subkeys[r]) == 6):  # next
                subkeys[r+1].append(key[i*4:(i*4)+4])
            else:
                subkeys[r].append(key[i*4:(i*4)+4])

        key = shift6(key)

    return subkeys


def shift6(key):
    first6 = key[0:6]
    others = key[6:]
    key = others+first6
    return key

# a^x mod n
def fastExpo(a, x, n):
    if a == 0:
        return 0
    if x == 0:
        return 1
    r = 1
    e = x
    b = a % n

    while e > 0:
        y = e % 2
        r = (r*pow(b, y)) % n
        b = (b*b) % n
        e = e//2
    return r


def round(text, keys):
    for i in range(5):

        text[0] = mult_mod17(text[0], keys[i][0])
        text[1] = add_mod16(text[1], keys[i][1])
        text[2] = add_mod16(text[2], keys[i][2])
        text[3] = mult_mod17(text[3], keys[i][3])
    return text

def decrypt_keys(keys):
    Y = [[] for i in range(5)]
    for i in range(len(keys)):  # ligne
        for j in range(6):  # col
            if(j == 0 or j == 3):  # inv mult mod 17
                Y[i].append(inv_mult_mod17(keys[len(keys)-i-1][j]))
            elif(j == 1 or j == 2):  # inv add mod 16
                Y[i].append(inv_add_mod16(keys[len(keys)-i-1][j]))
            elif(j > 3):
                if(i >= 4):
                    return Y
                Y[i].append(keys[len(keys)-i-2][j])


# 32 bit key
key = '11011100011011110011111101011001'



# 16 bit plain text
originalText = '1001110010101100'
print("original text:",originalText)

text = []
for i in range(4):
    text.append(originalText[i*4:(i*4)+4])

keys = encrypt_keys(key)
print("encryption keys :")
for i in range(len(keys)):
    print(keys[i])


round(text,keys)
print("ciphertext :",text)

keys2 = decrypt_keys(keys)
print("decryption keys :")
for i in range(len(keys2)):
    print(keys2[i])


round(text,keys2)
print("decoded:",text)










