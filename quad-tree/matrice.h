#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include <limits.h>


typedef enum _error_code {
ok,
out_of_bounds, 
memory_error, 
overflow, 
uninitialized
}error_code;

typedef struct _matrix {
int32_t m, n;
int32_t ** data;
} matrix;
error_code matrix_alloc(matrix *mat, int32_t m, int32_t n);
error_code matrix_init(matrix *mat, int32_t m, int32_t n, int32_t val);
error_code matrix_destroy(matrix *mat);
error_code matrix_init_from_array(matrix *mat, int32_t m, int32_t n, int32_t data[]);
error_code matrix_clone(matrix *cloned, const matrix mat);
error_code matrix_transpose(matrix *transposed, const matrix mat);
error_code matrix_print(const matrix mat);
error_code matrix_extract_submatrix(matrix *sub, const matrix mat, int32_t m0, int32_t m1, int32_t n0, int32_t n1);
bool matrix_is_equal(matrix mat1, matrix mat2);
error_code matrix_get(int32_t *elem, const matrix mat, int32_t ix, int32_t iy);
error_code matrix_set(matrix mat, int32_t ix, int32_t iy, int32_t elem);
error_code matrix_map_ip(matrix mat, void (*foo)(int *, int32_t), int32_t multiplier);
void mult(int *a, int b);
int matrix_sum(matrix mat);
error_code matrix_map(matrix *mapped, const matrix mat, void (*foo)(int *, int32_t), int32_t multiplier);

#endif