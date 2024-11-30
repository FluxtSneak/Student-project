#include "stack.h"
#include <string.h>

int main(){
    
    // stack s;
    // char a='r';
    // stack_init(&s,1);
    // push(&s,&a);
    // char* str=malloc(sizeof(char)*2);
    // str[0]=*(char*)peek(s);
    // str[1]='\0';
    // printf("%c\n",str[0]);
    // stack_destroy(&s);
    // free(str);
    //char str[] = "((1*2)/3-4)/(5+6)";
    char str[] = "1+2*3";
    int len=strlen(str);
    int len_post=len+1;
    printf("%d\n",len_post);
    char* post= malloc(sizeof(char)*len_post);
    to_postfix(str,post);
    //printf("%c\n",post[3]);
    printf("%s",post);
    printf("\n");
    free(post);

    return 0;
}