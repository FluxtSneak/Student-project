#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <math.h>  
#include <stdbool.h>    
#include "generic_vector.h"   

bool isEven(void* a){    
    return *(int*)a%2==0;    
}
void * square(void * a){
    *(int*)a*=*(int*)a;
    return a;
}

int main(){
    lst_vector test = lst_vector_init();
    printf("taille %d \n\n", lst_vector_length(&test));
    int a = 1;
    int b = 2;
    int c = 3;
    lst_vector_push(&test, &a);
    lst_vector_push(&test, &b);
    lst_vector_push(&test, &c);
    vec_print(test);
    printf("taille %d \n\n", lst_vector_length(&test));
    int d=4;
    lst_vector_insert(&test, &d, 2);
    vec_print(test);
    element poped=lst_vector_pop(&test);
    printf("poped = %d\n\n", *(int*)poped.data);
    vec_print(test);
    lst_vector ah=lst_vector_map(&test,square);
    lst_vector bl=lst_vector_filter(&ah,isEven);
    vec_print(ah);
    vec_print(bl);
    lst_vector_empty(&bl);
    lst_vector_empty(&test);
    lst_vector_empty(&ah);
    

    return 0;
}