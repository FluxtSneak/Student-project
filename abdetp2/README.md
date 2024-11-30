# abdetp2

# requierments 

pickle
yaml

# lancement des nodes

Les nodes se lancent comme demandé dans l'énoncé, avec un paramètre INIT ou WAIT comme dernier argument.
socket.getpeername() ne fonctionnne que sur des noeuds déployé dans un réseau (donc pas en local avec 127.0.0.1). 
DOIT ÊTRE LANCE SUR EXOSCALE, AZURE ou GOOGLE, OU SUR UN LAN.

# affichage

Chaque node affiche sur sa sortie standard les noeuds qui se sont connecté à lui, pui une fois l'algorithme terminé, affiche sa table de routage.

# Example lancement

## lancement sur tous les noeuds sauf 1
python3 node.py 9999 neighbour-x.yaml WAIT

## lancement sur le noeud initiant l'algo
python3 node.py 9999 neighbour-x.yaml INIT