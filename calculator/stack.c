#include "stack.h"
#include <string.h>

bool is_empty(stack s){
    return s.top==-1;
}
bool is_full(stack s){
    return s.capacity==s.top+1;
}
void stack_init(stack *stk, int capacity){
    stk->data=malloc(sizeof(void*)*capacity);
    stk->capacity=capacity;
    stk->top=-1;
}
void stack_destroy(stack *stk){
    free(stk->data);
    stk->top=-1;
    stk->capacity=-1;
}
void push(stack *stk, void* value){
    if(!is_full(*stk)){                
        stk->top++;
        stk->data[stk->top]=value;
    }
}

void *peek(stack stk){
    if(!is_empty(stk)){
        return stk.data[stk.top];
    }
    return NULL;
}

void * pop(stack *stk){
    if(!is_empty(*stk)){
        void* tmp=stk->data[stk->top];
        stk->top--;
        return tmp;
    }
    return NULL;
}

int stack_count(stack *stk){
    return stk->top+1;
}
void stack_transfert(stack *stk, stack *stk2){
    push(stk2, pop(stk));
}
int getPrio(char c) {
  switch (c) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  case '^':
    return 3;
  default:
    return 0;
  }
}
bool isOpperator(char c) {
  return c == '+' || c == '-' || c == '/' || c == '^' || c == '*'|| c == '(' || c == ')';
}
void to_postfix(char *infix,char *postfix){
    int length =strlen(infix);
    int ind_post=0;
    //int prio=0;
    stack s;
    stack_init(&s,length);
    for(int i =0; i<length;i++){
        char *current =&infix[i];
        if(!isOpperator(*current)){ //if is a number
            postfix[ind_post]=infix[i];
            ind_post++;
            continue;
        }
        else if(*current=='('){ //if '(' push with prio 0
            push(&s, &infix[i]);
            //prio=0;
        }
        else if(isOpperator(*current)){  //if is +-*/^ 
            if(is_empty(s) ||getPrio(*current)>getPrio(*(char*)peek(s))){ //check prio > top stack prio
                push(&s,&infix[i]);
                //prio =getPrio(infix[i]);
            }
            else{
                //unstack until top prio<current prio or stack empty
                while(getPrio(*(char*)peek(s))>getPrio(infix[i])&&!is_empty(s)){ 
                    postfix[ind_post]=*(char*)pop(&s);
                    ind_post++;
                    //prio=getPrio(*(char*)peek(s));
                }
                //while done i can push my new opp in stack
                push(&s,&infix[i]);
                //prio=getPrio(*(char*)peek(s));
            }
        }
        //if ) unstack until ( is on the top of stack, then unstack ( too
        else if(*current==')'){
            while(*(char*)peek(s)!='('){
                postfix[ind_post]=*(char*)pop(&s);
                ind_post++;
                //prio=getPrio(*(char*)peek(s));
            }
            pop(&s);
            //prio=getPrio(*(char*)peek(s));
        }
    }
    //Once every char is done, just pop all the stack in the postfix expr
    while(!is_empty(s)){
        postfix[ind_post]=*(char*)pop(&s);
        ind_post++;
    }
    printf("%d\n",ind_post);
    postfix[ind_post]='\0';
    stack_destroy(&s);
}