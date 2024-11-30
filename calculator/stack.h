#ifndef _STACK_H
#define _STACK_H
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack{
    void **data;
    int top;
    int capacity;
}stack;

bool is_empty(stack s);
bool is_full(stack s);
void stack_init(stack *stk, int capacity);
void stack_destroy(stack *stk);
void push(stack *stk, void * value);
void * peek(stack stk);
void *pop(stack *stk);
int stack_count(stack *stk);
void stack_transfert(stack *stk, stack *stk2);
void to_postfix(char *infix,char *postfix);
int get_prio(char c);
bool isOpperator(char c);


#endif
