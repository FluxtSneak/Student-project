#include"pointer_sort.h"


int main(){
    int a [10];
    int** p;

    for(int i=0;i<10;i++){
        a[i]=rand()%100;
    }
    print_tab(a, 10);
    p=pointer_sort(a, 10);
    print_tab(a, 10);
    print_tab_ptr(p, 10);
    free(p);

    return 0;

}