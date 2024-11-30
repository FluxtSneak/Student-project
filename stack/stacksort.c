#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include "tris.h"
#include <stdlib.h>
#include <time.h>

bool greater(int32_t a, int32_t b){
    if(a>b){
        return true;
    }
    return false;
}

void swap_value(int32_t *ind1, int32_t *ind2){
    int tmp = *ind1;
    *ind1= *ind2;
    *ind2=tmp;
}

void print_array(int32_t *arr, int32_t size){
    for(int i=0; i< size;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void arraycopy(int32_t *sorted, const int32_t *const orig,int32_t nitems){
    for(int i=0; i<nitems;i++){
        sorted[i]=orig[i];
    }
}
void stack_init(stack *stk, int capacity){
    stk->data=malloc(sizeof(int)*capacity);
    stk->capacity=capacity;
    stk->sommet=-1;
}
void stack_destroy(stack *stk){
    free(stk->data);
    stk->sommet=-1;
    stk->capacity=-1;
}
void stack_empile(stack *stk, int value){
    if(!stack_isFull(stk)){
        stk->sommet++;
        stk->data[stk->sommet]=value;
    }   
}
int stack_depile(stack *stk){    
    stk->sommet-=1;
    return stk->data[stk->sommet+1];    
}
bool stack_isEmpty(stack *stk){
    return stk->sommet==-1;
}
bool stack_isFull(stack *stk){
    return stk->sommet==stk->capacity-1;
}
int stack_count(stack *stk){
    return stk->sommet+1;
}
void stack_transfert(stack *stk, stack *stk2){
    stack_empile(stk2, stack_depile(stk));
}




void sort(int32_t *sorted, const int32_t *const orig, int32_t nitems, bool (*comp)(int32_t, int32_t)){

    stack g,d;
    stack_init(&g, nitems);
    stack_init(&d, nitems);
    stack_empile(&g, orig[0]);
    for(int i=1; i<nitems;i++){

        while(orig[i]<g.data[g.sommet]&&!stack_isEmpty(&g)){
            stack_transfert(&g,&d);
        }
        while(orig[i]>d.data[d.sommet]&& !stack_isEmpty(&d)){
            stack_transfert(&d, &g);
        }
        stack_empile(&g,orig[i]);
    }
    while(!stack_isEmpty(&d)){
        stack_transfert(&d, &g);
    }
    for(int i=0; i<nitems; i++){
        sorted[i]=stack_depile(&g);
    }
    stack_destroy(&d);
    stack_destroy(&g);

}

