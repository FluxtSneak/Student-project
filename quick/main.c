#include <math.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "tris.h"

int main(int argc, char **argv){
    srand(time(NULL));   //change seed of rand
    if(argc<2) EXIT_FAILURE;
    int size= atoi(argv[1]);
    int32_t tab[size];
    int32_t quick_sorted[size];
    for(int i=0; i<size;i++){
        tab[i]= rand()%50;
    }
    print_array(tab,size);
    sort(quick_sorted, tab, size, greater);
    print_array(quick_sorted,size);
    

    return 0;

    

    



}