#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>       /* log() */
#include "matrice.h"   /*matrice*/

error_code matrix_init(matrix *mat, int32_t m, int32_t n){
    mat->data = malloc(m*sizeof(int*));

    for (int i =0;i<m;i++){
        mat->data[i]=malloc(m*sizeof(int));
    }
    mat->n=n;
    mat->m=m;
    return ok;
}
error_code matrix_destroy(matrix *mat){
    int a= mat->m;

    for (int i=0; i<a;i++){
        free(mat->data[i]);
    }
    free(mat->data);
    return ok;
}
error_code matrix_init_from_array(matrix *mat, int32_t m, int32_t n, int32_t data[]){
    mat->data = malloc(m*sizeof(int*));

    for (int i =0;i<m;i++){
        mat->data[i]=malloc(m*sizeof(int));

    }
    int ind_tab=0;

    for(int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            mat->data[i][j]=data[ind_tab++];            
        }
    }
    mat->n=n;
    mat->m=m;
    return ok;
}
error_code matrix_clone(matrix *cloned, const matrix mat){
    
}