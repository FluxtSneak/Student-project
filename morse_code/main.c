#include <stdio.h>
#include <stdlib.h>
#include "morse.h"

int main(int argc, char** argv) {
   arbre tree = arbre_build("code-morse.txt");
   print(tree,1);   // impression de l'arbre
   if (2 == argc) {
      decoder_fichier(argv[1],tree);
      printf("\n");
   }
   char alphabet_morse[26][6];
   table_build("code-morse.txt",26,6,alphabet_morse);
   if (3 == argc) {
      encoder_fichier(argv[2],26,6,alphabet_morse);
      printf("\n");
   } 
   return 0;
}