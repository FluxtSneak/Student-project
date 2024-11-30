#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void show(int i){    
    if(i <1)return;
    show(i-1);
    printf(" %d", i-1);
}


int main(){
    show(10);
    return 0;
}