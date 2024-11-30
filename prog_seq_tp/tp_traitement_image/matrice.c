#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>       /* log() */
#include "matrice.h"   /*matrice*/
#include <limits.h>
error_code matrix_alloc(matrix *mat, int32_t m, int32_t n){
    if(m<=0||n<=0){
        return out_of_bounds;
    }
    mat->data = malloc(m*sizeof(int*));
    for (int i =0;i<m;i++){
        mat->data[i]=malloc(n*sizeof(int));
    }
    if(mat->data==NULL){
        return memory_error;
    }
    mat->n=n;
    mat->m=m;
    return ok;
}
error_code matrix_init(matrix *mat, int32_t m, int32_t n, int32_t val){
    if(m<=0||n<=0){
        return memory_error;
    }
    mat->data = malloc(m*sizeof(int*));
    for (int i =0;i<m;i++){
        mat->data[i]=malloc(n*sizeof(int));
    }
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            mat->data[i][j]=val;
        }
    }
    if(mat->data==NULL){
        return memory_error;
    }
    mat->n=n;
    mat->m=m;
    return ok;
}
error_code matrix_destroy(matrix *mat){
    if(mat->data==NULL){
        return uninitialized;
    }

    for (int i=0; i<mat->m;i++){
        free(mat->data[i]);
    }
    free(mat->data);
    mat->m=-1;
    mat->n=-1;
    return ok;
}
error_code matrix_init_from_array(matrix *mat, int32_t m, int32_t n, int32_t data[]){
    if(data==NULL){
        return memory_error;
    }
    int size =m*n;
    matrix_alloc(mat, m, n);
 
    int ind_tab=0;

    for(int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            if(ind_tab>size){
                return out_of_bounds;
            }
            mat->data[i][j]=data[ind_tab++];            
        }
    }
    if(mat->data==NULL){
        return memory_error;
    }
    mat->n=n;
    mat->m=m;
    return ok;
}
error_code matrix_clone(matrix *cloned, const matrix mat){
    cloned->m= mat.m;
    cloned->n=mat.n;
    matrix_alloc(cloned, mat.m, mat.n);
    for(int i=0;i<mat.m;i++){
        for (int j=0; j<mat.n;j++){
            cloned->data[i][j]=mat.data[i][j];
        }
    }
    if(cloned->data==NULL){
        return memory_error;
    }
    return ok;
}
error_code matrix_transpose(matrix *transposed, const matrix mat){
    transposed->m=mat.n;
    transposed->n=mat.m;
    matrix_alloc(transposed,transposed->m, transposed->n);
    for(int i=0; i<mat.m;i++){
        for (int j=0; j<mat.n; j++){
            transposed->data[j][i]=mat.data[i][j];
        }
    }
    if(transposed->data==NULL){
        return memory_error;
    }
    return ok;
}
error_code matrix_print(const matrix mat){
    if(mat.data==NULL){
        return uninitialized;
    }
    for(int i=0; i<mat.m;i++){
        for (int j=0; j<mat.n;j++){
            printf("%d ",mat.data[i][j]);
        }
        printf(" \n");
    }
    for(int i =0 ;i<mat.n;i++){
        printf("-");
    }
    printf("\n");
    return ok;
}
error_code matrix_extract_submatrix(matrix *sub, const matrix mat, int32_t m0, int32_t m1, int32_t n0, int32_t n1){
    if(m1-m0<0||n1-n0<0||m1-m0>mat.m||n1-n0>mat.n){
        return out_of_bounds;
    }
    sub->m=m1-m0;
    sub->n=n1-n0;
    matrix_alloc(sub, sub->m, sub->n);
    for (int i=0; i<sub->m;i++){
        for (int j=0; j<sub->n;j++){
            sub->data[i][j]=mat.data[m1-sub->m+i][n1-sub->n+j];
        }
    }
    if(sub->data==NULL){
        return memory_error;
    }      
    return ok;
}
bool matrix_is_equal(matrix mat1, matrix mat2){
    if(mat1.data==NULL||mat2.data==NULL){
        return memory_error;
    }
    if(mat1.m==mat2.m && mat1.n ==mat2.n){
        for (int i=0; i<mat1.m;i++){
            for (int j=0; j<mat1.n;j++){
                if (mat1.data[i][j]!=mat2.data[i][j]) return false;
            }
        }
        return true;
    }
    return false;
}
error_code matrix_get(int32_t *elem, const matrix mat, int32_t ix, int32_t iy){
    if(ix<0||ix>mat.m||iy<0||iy>mat.n){
        return out_of_bounds;
    }
    if(mat.data[ix][iy]>INT_MAX){
        return overflow;
    }
    *elem=mat.data[ix][iy];
    return ok;
}
error_code matrix_set(matrix mat, int32_t ix, int32_t iy, int32_t elem){
    if(ix<0||ix>mat.m||iy<0||iy>mat.n){
        return out_of_bounds;
    }
    if(elem>INT_MAX){
        return overflow;
    }
    mat.data[ix][iy]=elem;
    return ok;
}
void mult(int *a, int b){
    *a*=b;
}
int matrix_sum(matrix mat){
    int res=0;
    for(int i=0; i< mat.m;i++){
        for(int j=0;j<mat.n;j++){
            res+=mat.data[i][j];
        }
    }
    return res;
}
error_code matrix_map_ip(matrix mat, void (*foo)(int *, int32_t), int32_t multiplier){
    if(mat.data==NULL){
        return uninitialized;
    }
    for (int i=0;i<mat.m;i++){
        for(int j=0;j<mat.n;j++){
            foo(&mat.data[i][j], multiplier);
        }
    }
    if (mat.data==NULL){
        return memory_error;
    }

    return ok;
}
error_code matrix_map(matrix *mapped, const matrix mat, void (*foo)(int *, int32_t), int32_t multiplier){
    matrix_clone(mapped, mat);
    if(mapped->data==NULL){
        return uninitialized;
    }
    for (int i=0;i<mat.m;i++){
        for(int j=0;j<mat.n;j++){
            foo(&mapped->data[i][j], multiplier);
        }
    }
    if (mapped->data==NULL){
        return memory_error;
    }
    return ok;
}