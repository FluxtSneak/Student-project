#include "morse.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
  char lettre;
  struct _node *left;
  struct _node *right;
} node;

arbre arbre_build(char *filename) {
  arbre tree = calloc(1, sizeof(node));
  tree->lettre = '?';
  FILE *fp = fopen(filename, "r");
  assert(NULL != fp);
  char c[6];
  while (!feof(fp)) {
    fgets(c, 6, fp);
    place(c, &tree);
  }

  fclose(fp);
  return tree;
}

void arbre_destroy(arbre tree) {

  if (tree != NULL) {
    if (tree->left != NULL) {
      arbre_destroy(tree->left);
    }
    if (tree->right != NULL) {
      arbre_destroy(tree->right);
    }
    free(tree);
  }
}

void table_build(char *filename, int n, int m, char alphabet_morse[n][m]) {
  FILE *fp = fopen(filename, "r");
  assert(NULL != fp);

  char line[10];

  for (int i = 0; i < n; i++) {
    fgets(line, 10, fp);

    int j = 0;
    while (line[j] != '\r') {
      alphabet_morse[i][j] = line[j];
      j++;
    }
    alphabet_morse[i][j] = '\0';
  }

  fclose(fp);
}



char decoder(char *code, arbre tree) {
   arbre tmp = tree;
   for (int i = 0; i < (int)strlen(code); i++) {
      if (tmp == NULL) {
         return '?';
      }
      if (code[i] != '-' && code[i] != '.') {
         break;
      }
      if(code[i]=='.')tmp=tmp->left;
      else tmp=tmp->right;
   }
   if (tmp == NULL) {
      return '?';
   }
return tmp->lettre;
}

void decoder_fichier(char *filename, arbre tree) {
   // lecture d'un mot de caract�res dans 'A'..'Z'
   FILE *fp = fopen(filename, "r");
   assert(NULL != fp);
   int lg = 0;
   char code[6];
   while (!feof(fp)) {
      char ch = (char)fgetc(fp);
      switch (ch) {
         case '/':
            printf(" ");
            break;
         case ' ':
            printf("%c",decoder(code, tree));
            lg=0;
            break;
         default:
            code[lg]=ch;
            lg++;
            break;
      }
   }
   fclose(fp);
}

void place(char *chaine, arbre *tree) {
  arbre tmp = *tree;
  for (int i = 1; i < (int)strlen(chaine); i++) {
    char ch = chaine[i];
    if (ch != '-' && ch != '.') {
      break;
    }
    if (ch == '.') {
      if (tmp->left == NULL) {
        tmp->left = calloc(1, sizeof(node));
        tmp = tmp->left;
        tmp->lettre = '?';
      }
    } else {
      if (tmp->right == NULL) {
        tmp->right = calloc(1, sizeof(node));
        tmp = tmp->right;
        tmp->lettre = '?';
      }
    }
  }
  tmp->lettre = chaine[0];
}

void print(arbre tree, int niv) {
  if (tree == NULL) {
    return;
  }
  print(tree->left, niv + 1);
  for (int i = 0; i < niv; i++) {
    printf(" -");
  }
  printf(" %c\n", tree->lettre);

  print(tree->right, niv + 1);
}

void encoder_fichier(char *filename, int n, int m, char alphabet_morse[n][m]) {
  FILE *fp = fopen(filename, "r");
  assert(NULL != fp);

  while (!feof(fp)) {
    char ch = (char)fgetc(fp);

    switch (ch) {
    case ' ':
      printf("/");
      break;

    default: // lettres
      for (int i = 0; i < n; i++) {
        if (alphabet_morse[i][0] == ch) {
          for (int j = 1; j < (int)strlen(alphabet_morse[i]); j++) {
            printf("%c", alphabet_morse[i][j]);
          }
        }
      }
      printf(" ");
      break;
    }
  }
  fclose(fp);
}
