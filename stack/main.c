#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "tris.h"

int main(int argc, char **argv){
    srand(time(NULL));   //change seed of rand

    int size= atoi(argv[1]);
    int32_t tab[size];
    int32_t stack_sorted[size];
    for(int i=0; i<size;i++){
        tab[i]= rand()%500;
    }
    print_array(tab,size);
    sort(stack_sorted, tab, size, greater);
    print_array(stack_sorted,size);
    

    return 0;

    

    



}