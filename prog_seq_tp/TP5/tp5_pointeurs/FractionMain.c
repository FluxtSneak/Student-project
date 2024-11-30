#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <math.h>       /* log() */
#include "Fraction.h"   /*fractions*/



int main(int argc, char **argv){

    if(argc!=6){
        printf("Need : \n 1 2 + 3 4 \n");
        return EXIT_FAILURE;
    }
    long num1 = atoi(argv[1]);
    unsigned long long int den1 = atoi(argv[2]);
    long num2 = atoi(argv[4]);
    unsigned long long int den2 = atoi(argv[5]);
    fraction_t *frac1 = frac_init(num1,den1);
    fraction_t *frac2 = frac_init(num2,den2);
    frac_print(frac1);
    frac_print(frac2);
    fraction_t *frac3;

    
    if(*argv[3]=='+')frac3=frac_add(frac1,frac2);
    else if(*argv[3]=='-')frac3=frac_sub(frac1,frac2);
    else if(*argv[3]=='*')frac3=frac_mult(frac1,frac2);
    else if(*argv[3]=='/')frac3=frac_div(frac1,frac2);
    frac_print(frac3);

    free(frac1);
    free(frac2);
    free(frac3);
    
    frac3=pi1();
    free(frac3);
    //pi1_wo_frac();

    return 0;
}