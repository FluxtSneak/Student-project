#include"generic_vector.h"
#include <assert.h> 
#include <stdlib.h>

lst_vector lst_vector_init(){

    lst_vector a=NULL;
    return a;
}

int lst_vector_length(lst_vector *v){
    if (v==NULL)return -1;
    int cpt=0;
    element* a = *v;
    while (a!=NULL){
        a=a->next;
        cpt++;
    }
    return cpt;
}

element lst_vector_push(lst_vector *v, void *data){
    assert(v!=NULL);
    element *new=malloc (sizeof(element));
    new->data =data;
    new->next=(*v);
    *v=new;
    return *new;
}

element lst_vector_pop(lst_vector *v){
    assert(v!=NULL);
    element *a=*v;
    *v=(*v)->next;
    element b= *a;
    free(a);    
    return b;
}

element *lst_vector_pos(lst_vector *v, int index){
    element * a= *v;
    for (int i =0; i<index; i++){
        a=a->next;
    }
    return a;
}

lst_vector lst_vector_set(lst_vector *v, int index, void *data){
    assert(v!=NULL);
    if(index+1>lst_vector_length(v)){
        printf("Tatata, index out of range of vector.");
        return *v;
    }
    element *a=lst_vector_pos(v,index);
    a->data=data;

    return *v;
}

element lst_vector_get(lst_vector *v, int index){
    assert(v!=NULL);
    assert(lst_vector_length(v)>=index+1);
    element *a=lst_vector_pos(v, index);
    return *a;
}

element lst_vector_remove(lst_vector *v, int index){
    assert(v!=NULL);
    assert(lst_vector_length(v)>=index+1);
    element *a=lst_vector_pos(v, index-1);    
    element *rem=a->next;
    a->next=rem->next;

    return *rem;
}

lst_vector lst_vector_insert(lst_vector *v, void *data, int index){
    assert(v!=NULL);
    assert(lst_vector_length(v)<=index+1);
    if(index==0)lst_vector_push(v,data);
    else{
        element *a=lst_vector_pos(v,index-1);
        lst_vector_push(&a->next,data);
    }    
    return *v;
}

void lst_vector_empty(lst_vector *v){
    assert(v!=NULL);
    element *tmp;
    while ((*v)->next!=NULL){
        tmp=*v;
        *v=(*v)->next;
        free(tmp);
    }
    free(*v);
}
void vec_print(lst_vector v){
    while (v!=NULL){
        printf("%d  ", *(int *)(v->data));
        v=(v)->next;
    }
    printf("\n");
}



lst_vector lst_vector_map(lst_vector *v, void *(*f)(void *)){
    assert(v!=NULL);
    lst_vector new=lst_vector_init();
    int i =0;
    while (i<lst_vector_length(v)){
        lst_vector_insert(&new,f(lst_vector_get(v, i).data),i);        
        i++;
    }    
    return new;
}

lst_vector lst_vector_filter(lst_vector *v, bool (*f)(void *)){
    assert(v!=NULL);
    lst_vector new=lst_vector_init();
    element *a=*v;
    int i =0;
    while (a!=NULL){
        if(f(a->data)){
        lst_vector_insert(&new,a->data,i);        
        i++;
        }
        a=a->next;
    }    
    return new;
 }
