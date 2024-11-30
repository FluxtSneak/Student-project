#ifndef _QUEUE_lst_LIST_H_
#define _QUEUE_lst_LIST_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct _pixel {
    int line;
    int col;
    
} pixel;

typedef pixel T;

typedef struct _element {
    T data;
    struct _element *next;
} element;


typedef struct _queue_lst{
    element *firstIn;
    element *lastIn;
} queue_lst;


queue_lst queue_create_lst();
void queue_lst_destroy(queue_lst* Q);
void queue_insert_lst(queue_lst* Q,pixel val);
T queue_extract_lst(queue_lst* Q);
T queue_first_lst(queue_lst Q);
T queue_head_lst(queue_lst Q);
bool queue_is_empty_lst(queue_lst Q);
int queue_count_lst(queue_lst Q);
void print_queue_lst(queue_lst Q);

#endif