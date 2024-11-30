#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <math.h>       /* log() */
#include "matrice.h"   /*fractions*/



int main(){
    matrix mat;
    matrix_init(&mat, 4, 5);
    matrix_destroy(&mat);

    return 0;
}