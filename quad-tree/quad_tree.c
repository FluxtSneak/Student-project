#include "quad_tree.h"
#include "matrice.h"
#include <limits.h>
#include <math.h>
#define CHILDREN 4



node* tree_create(int depth) {
   node* a = calloc(1,sizeof(node));
   if (depth > 0) {
      for (int i=0;i<CHILDREN;i++) {
         a->child[i] = tree_create(depth-1);
      }
   }
   return a;
}

void tree_destroy(node* nd){
   if(!is_leaf(nd)){
      for(int i=0;i<CHILDREN;i++){
         tree_destroy(nd->child[i]);
      }
   }
   free(nd);
}

//Utils functions

bool is_leaf(node* nd) { 
    return NULL == nd->child[0];
}

void print(node* arbre,int decal,char* sep) {
   if (NULL != arbre) {
      for (int i=0;i<decal;i++) { 
         printf("%s",sep);
      }
      printf("%d\n",(int)arbre->ave);
      decal++;
      if (!is_leaf(arbre)) {
         for (int i=0;i<CHILDREN;i++) {
            print(arbre->child[i],decal,sep);
         }
      }
   } 
}

void sum(node* arbre) {
   if (!is_leaf(arbre)) {
      for (int i=0;i<CHILDREN;i++) {
         sum(arbre->child[i]);
      }
      for (int i=0;i<CHILDREN;i++) {
         arbre->ave += arbre->child[i]->ave;
      }
   }
}

int nbNodes(node *arbre){
   int sum=1;
   if(!is_leaf(arbre)){
      for(int i =0;i<CHILDREN;i++){
         sum+=nbNodes(arbre->child[i]);
      }
   }
   return sum;
}

int tree_max(node* tree){
   int max_tree= INT_MIN;
   if(!is_leaf(tree)){
      for(int i=0;i<CHILDREN;i++){
         max_tree=max(max_tree, tree_max(tree->child[i]));
         max_tree=max(max_tree, tree->child[i]->ave);
      }
   }
   return max_tree;
}

int max(int x,int y) {
   if(x>y)return x;
   return y;
}

int array_max(int size,int tab[size]) {
   int m = INT_MIN;
   for (int i=0;i<size;i++) {
      m = max(m,tab[i]);
   }
   return m;
}

void average(node * tree){
   if(!is_leaf(tree)){
      tree->ave=0;
      tree->ave_sq=0;
      for(int i=0;i<CHILDREN;i++){
         average(tree->child[i]);
         tree->ave+=tree->child[i]->ave;
         tree->ave_sq+=tree->child[i]->ave_sq;
      }
      tree->ave/=CHILDREN;
      tree->ave_sq/=CHILDREN;
      
   }
}

void swap(node *a, node *b){
    node tmp=*a;
    *a=*b;
    *b=tmp;

}

int depth(node* a) {
   int p[CHILDREN] = {0};
   if (is_leaf(a)) {
      return 0;
   } else {
      for (int i=0;i<CHILDREN;i++) {
         p[i] = 1+depth(a->child[i]);
      }
      return array_max(CHILDREN,p);
   }
}

node* position(int m,int n,node* a,int d) { 
   node* crt = a;
   //tant qu’on n’est pas sur une feuille, déplacer 
   // <crt> sur un enfant selon valeur du d­-ième bit de <m> et <n>
   if(!is_leaf(a)){
      int i =(m>>d)&1;
      int j=(n>>d)&1;
      crt=crt->child[(i<<1)+j];
      crt=position(m,n,crt,d-1);
   }
   return crt; 
}

double compressRate(int oldSize, int newSize){
   return 100-(double)newSize*100/oldSize;
}


//Utilisation PGM

node *tree_from_file(char *filename){
   pgm img;
   pgm_read_from_file(&img, filename);
   node * tree=tree_create((int)log2(img.pixels.m));
   matrix2tree(&img.pixels, tree);
   average(tree);
   matrix_destroy(&img.pixels);
   return tree;

}

void tree2file(node* tree, char* filename){
   matrix mat;
   pgm img;
   img.max=tree_max(tree);
   int size = pow(2,depth(tree));
   
   matrix_alloc(&mat, size, size);
   tree2matrix(tree, &mat);
   img.pixels=mat;
   pgm_write_to_file(&img, filename);
   matrix_destroy(&mat);
}

void matrix2tree(matrix* mat,node* arbre) {
   int d = depth(arbre)-1; 
   for (int m=0;m<mat->m;m++) { 
      for (int n=0;n<mat->n;n++) { 
         node* crt = position(m,n,arbre,d); 
         crt->ave = mat->data[m][n];
         crt->ave_sq = crt->ave*crt->ave; 
      } 
   }
}

void tree2matrix(node *arbre, matrix *mat){
   int d = depth(arbre)-1;
   for(int m=0;m<mat->m;m++){
      for(int n=0;n<mat->n;n++){
         node* crt=position(m,n,arbre,d);
         mat->data[m][n]=(int)crt->ave;
      }
   }
}

void symetry(node* arbre,int bit) {
   if (!is_leaf(arbre)) { 
      for (int i=0;i<CHILDREN;i++) {
         if (i < (i^bit)) {
            swap(arbre->child[i],arbre->child[i^bit]);
         }
      }
      for (int i=0;i<CHILDREN;i++) {
         symetry(arbre->child[i],bit);
      }
   }
}

void compress(node *arbre, double seuil){
   if(!is_leaf(arbre)){
      for(int i=0;i<CHILDREN;i++){
         compress(arbre->child[i],seuil);
      }
      bool lastBranch=true;
      for(int t=0;t<CHILDREN;t++){
         if(!is_leaf((arbre->child[t]))) lastBranch=false;
      }
      if(lastBranch){
         double ave2=arbre->ave*arbre->ave;
         double var= arbre->ave_sq-(ave2);
         
         if(var<seuil*seuil*ave2){
            for(int j=0; j<CHILDREN; j++){
               free(arbre->child[j]);
               arbre->child[j]=NULL;
            }
         }
      }
   }
}