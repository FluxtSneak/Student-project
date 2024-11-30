#include"queue_list.h"

queue_lst queue_create_lst(){
    queue_lst Q;
    Q.firstIn=Q.lastIn=NULL;
    return Q;
}

void queue_lst_destroy(queue_lst* Q){
    while(Q->firstIn!=NULL){
        element *tmp=Q->firstIn->next;
        free(Q->firstIn);
        Q->firstIn=tmp;                
    }
}

void queue_insert_lst(queue_lst* Q,pixel val){
    
    element *e=malloc(sizeof(element));
    e->data=val;
    e->next=NULL;
    if(queue_is_empty_lst(*Q)){
        Q->firstIn=e;
        Q->lastIn=e;
        
    }else{       
        Q->lastIn->next=e;
    }
    Q->lastIn=e;
}

T queue_extract_lst(queue_lst* Q){
    T tmp=Q->firstIn->data;
    element *e=Q->firstIn;
    Q->firstIn=Q->firstIn->next;
    free(e);
    return tmp;

}

T queue_first_lst(queue_lst Q){
    return Q.firstIn->data;
}

T queue_head_lst(queue_lst Q){
    return Q.lastIn->data;
}

bool queue_is_empty_lst(queue_lst Q){
    return Q.firstIn==NULL;
}

int queue_count_lst(queue_lst Q){
    int cpt=0;
    while(Q.firstIn!=NULL){
        Q.firstIn=Q.firstIn->next;
        cpt++;
    }
    return cpt;
}
void print_queue_lst(queue_lst Q){
    while(Q.firstIn!=NULL){
        printf("%d et %d \n", Q.firstIn->data.line, Q.firstIn->data.col);
        Q.firstIn=Q.firstIn->next;        
    }
}