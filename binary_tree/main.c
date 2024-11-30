#include "binary_tree_lib.h"
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int test[10];
    for(int i =0;i<10;i++){
        test[i]=rand()/(RAND_MAX/100);
        printf("%d\n",test[i]);
    }
    node_t* tree=bst_create();
    for (int i =0;i<10;i++){
        tree=bst_insert(tree, test[i]);
        
    }
    bst_print(tree, 0);
    printf("min value is :%d\n\n",(bst_find_min_node(tree))->val);
    printf("max value is :%d\n\n",(bst_find_max_node(tree))->val);
    //bst_print(tree, 0);
    bst_destroy(tree);



    return 0;
}