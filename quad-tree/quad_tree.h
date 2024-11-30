#ifndef _QUAD_TREE_H
#define _QUAD_TREE_H

#include "matrice.h"
#include <string.h>
#include <math.h>
#include "pgm.h"


typedef struct _node {
  double ave;    // moyenne des valeurs des enfants, ou valeur de la feuille
  double ave_sq; // moyenne des carrés des valeurs des enfants
  struct _node *child[4];
} node;

// retourne un pointeur sur un arbre complet de profondeur <depth>
node* tree_create(int depth);
//détruit un arbre
void tree_destroy(node* nd);


//Utils functions :

//retourne si le noeud est une feuille
bool is_leaf(node* nd);

//affiche l'arbre dans la console (plus ou moins joliment, mais c'est affiché)
void print(node *arbre, int decal, char *sep);

//calcul la somme de la value des enfants
void sum(node *arbre);

//retourne le nombre de noeuds contenus dans l'arbre
int nbNodes(node *arbre);

//retourne la val max contenue par l'arbre
int tree_max(node* tree);

//compare deux valeurs et retourne la plus élevée
int max(int x,int y);

//retourne la val max d'un tableau
int array_max(int size,int tab[size]);

// stocke dans chaque noeud de <arbre>, la somme et celle des carrés
// des feuilles du sous­-arbre correspondant
void average(node *arbre);

// échange deux pointeurs
void swap(node *a, node *b);

// retourne la profondeur d'un arbre <nd>
int depth(node *nd);

// retourne un pointeur sur une feuille d'un arbre <a> de profondeur
// <d> qui correspond à une position <li>,<co> dans une image 2d2d
node *position(int li, int co, node *a, int d);

//retourne le taux de compression gagné grâce à la compression
double compressRate(int oldSize, int newSize);


//utilisation des images PGM

//construit un arbre à partir d'un fichier PGM
node *tree_from_file(char *filename);

//écrit une image PGM dans un fichier, à partir d'un arbre
void tree2file(node* tree, char* filename);

// transfère les données d'une image <mat> dans un arbre <arbre>
void matrix2tree(matrix *mat, node *arbre);

// transfère les données d'un arbre <arbre> dans une image <mat>
void tree2matrix(node *arbre, matrix *mat);

// permet d'obtenir une symétrie horizontale ou verticale en
// permutant les pointeurs <child[i]> et <child[i^bit]>
void symetry(node *arbre, int bit);

// récursivement on descend à l'avant­ dernier niveau de l'arbre
// et on supprime les enfants en remontant si l’écart­type
// est inférieur à <seuil>
void compress(node *arbre, double seuil);



#endif