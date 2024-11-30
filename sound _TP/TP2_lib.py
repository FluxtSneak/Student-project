#################################################################################
############         Manipulation des fichiers wave         #####################
#################################################################################

import wave as w
from struct import pack,unpack
from copy import deepcopy

######## Prend un fichier .wav MONO et retourne sa liste de valeurs et son sample rate.
######## Usage:  lst , sr = wav_to_list( name ), lst contient les valeurs et sr le sample rate.
######## name doit être un string avec le nom entier du fichier (".wav" compris).

def wav_to_list( name ):
    wro = w.open(name, "rb")
    length = wro.getnframes()
    uuu = []
    for t in range(length):
        aaa = unpack( 'h' , wro.readframes(1) )       
        uuu += [ int(aaa[0]) ]
    return uuu , wro.getframerate()

######## Transforme une liste en un wave_write object et save le fichier
######## en format wave MONO de nom name (qui est un string devant contenir le nom entier, avec .wav).
######## L'encodage est sur 16 bits.
######## Par défaut le sample_rate est de 44100Hz, mais peut être changé.
######## Il normalise automatiquement au maximum du son si norm = 1.
######## Attention, les valeurs dans la liste doivent etre des entiers entre -32678 et 32677.
######## (Si norm == 0, les valeurs sont castées en entiers mais on ne vérifie pas l'overflow.)


def list_to_wav( liste , name , sample_rate = 44100 , norm = 1):
    M = max( [abs( k ) for k in liste] )
    if norm and (M != 0):
        liste_norm = [ int( round(k/M*32677) ) for k in liste]
    else:
        liste_norm = deepcopy(liste)
        liste_norm = [int(k) for k in liste_norm]
    f = w.open( name ,'wb')
    f.setnchannels(1)
    f.setsampwidth(2)
    f.setframerate(sample_rate)
    f.setcomptype('NONE', 'none')
    print("start file maker")
    for k in liste_norm:
        data = pack('h',k)
        f.writeframes(data)
    print("end file maker")
    f.close()





