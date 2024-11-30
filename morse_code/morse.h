#ifndef _MORSE_H_
#define _MORSE_H_

typedef struct _node node;
typedef  node* arbre;

arbre morse_tree(char ** morse);
arbre arbre_build(char* filename);

void print(arbre tree, int niv);

char decoder(char *code, arbre tree);


void decoder_fichier(char *filename, arbre tree);

void encoder_fichier(char *filename, int n, int m, char alphabet_morse[n][m]);

void place(char *chaine, arbre *tree);

void table_build(char *filename, int n, int m, char alphabet_morse[n][m]);

void arbre_destroy(arbre tree);

#endif