#include "queue_tab.h"


//Créer une nouvelle queue vide
queue queue_create(){
    queue Q;
    Q.capacity=1;
    Q.data=malloc(Q.capacity*sizeof(T));
    Q.head=-1;
    return Q;
}
//Libérer le tableau, mettre la capacité à < -1
void queue_destroy(queue* Q){
    Q->capacity=-1;
    free(Q->data);
    Q->head=-1;
}
//Inserer un élement en début de queue
void queue_insert(queue* Q,T val){
    if(Q->capacity-1==Q->head)queue_resize(Q, Q->capacity+1);
    Q->head++;
    Q->data[Q->head]=val;
}
void queue_resize(queue* Q,int max) {
    Q->capacity = max;
    Q->data = realloc(Q->data,max*sizeof(T));
   
}
//Extraire un élément en tête de queue
T queue_extract(queue* Q){
    T tmp= Q->data[0];
    //décalage des valeures vers 0
    for (int i=0; i<Q->head; i++){
        Q->data[i]=Q->data[i+1];
    }
    Q->head--;
    queue_resize(Q, Q->capacity-1);
    return tmp;
}
//Consulter l'élément en tête de queue
T queue_first(queue Q){
    return Q.data[0];
}
//Consulter l'élément au début de queue
T queue_head(queue Q){
    return Q.data[Q.head];
}
//Tester si la queue est vide
bool queue_is_empty(queue Q){
    return Q.capacity==0 && Q.head==-1;
}
//Compter du nombre d'éléments de la queue:
int queue_count(queue Q){
    return Q.capacity;
}
void print_queue(queue Q){
    for(int i=0;i<Q.capacity; i++){
        printf("%d\n", Q.data[i]);
    }
}
