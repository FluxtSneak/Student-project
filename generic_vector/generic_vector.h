#ifndef _lst_vector_LIST_H_
#define _lst_vector_LIST_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct _element {
   void *data;
   struct _element* next;
} element;

typedef element* lst_vector;


lst_vector lst_vector_init();
int lst_vector_length(lst_vector *v);
element lst_vector_push(lst_vector *v, void *data);
element lst_vector_pop(lst_vector *v);
element *lst_vector_pos(lst_vector *v, int index);
lst_vector lst_vector_set(lst_vector *v, int index, void *data);
element lst_vector_get(lst_vector *v, int index);
element lst_vector_remove(lst_vector *v, int index);
lst_vector lst_vector_insert(lst_vector *v, void *data, int index);
void lst_vector_empty(lst_vector *v);
lst_vector lst_vector_map(lst_vector *v, void *(*f)(void *));
lst_vector lst_vector_filter(lst_vector *v, bool (*f)(void *));
void vec_print(lst_vector v);
lst_vector lst_vector_map(lst_vector *v, void *(*f)(void *));


#endif