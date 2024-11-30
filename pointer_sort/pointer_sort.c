#include "pointer_sort.h"
#include <sys/types.h>

int** pointer_sort(int* tab, int size){
    int** tab_ptr=malloc(sizeof(int*)*size);
    for(int i=0;i<size;i++){
        tab_ptr[i]=&tab[i];
    }
    
    for(int i=0; i<size;i++){
        int a=0;
        for(int j=0;j<size-i;j++){
            printf("ptr val:%d, cur val: %d\n",*tab_ptr[j],*tab_ptr[a]);
            if(*tab_ptr[j]>*tab_ptr[a])a=j;
        }
        int * tmp=tab_ptr[size-1-i];
        tab_ptr[size-1-i]=tab_ptr[a];
        tab_ptr[a]=tmp;
        
    }
    return tab_ptr;
}
void print_tab(int * tab, int size){
    for(int i=0; i<size;i++){
        printf("%d: %d\n",i,tab[i]);
    }
    printf("---------------\n");

}
void print_tab_ptr(int ** tab, int size){
    for(int i=0; i<size;i++){
        printf("%d: %d\n",i,*tab[i]);
    }
    printf("---------------\n");
}