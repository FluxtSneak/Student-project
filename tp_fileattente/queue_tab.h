#ifndef _QUEUE_TAB_H_
#define _QUEUE_TAB_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int32_t T;

typedef struct _queue {
   T* data;
   int head; //tete à l'index 0
   int capacity;
} queue;

//Créer une nouvelle queue vide
queue queue_create();
//Libérer le tableau, mettre la capacité à < -1
void queue_destroy(queue* Q);
//Redimensionner une queue
void queue_resize(queue* Q,int max);
//Inserer un élement en début de queue
void queue_insert(queue* Q,int val);
//Extraire un élément en tête de queue
T queue_extract(queue* Q);
//Consulter l'élément en tête de queue
T queue_first(queue Q);
//Consulter l'élément au début de queue
T queue_head(queue Q);
//Tester si la queue est vide
bool queue_is_empty(queue Q);
//Compter du nombre d'éléments de la queue:
int queue_count(queue Q);
void print_queue(queue Q);

#endif