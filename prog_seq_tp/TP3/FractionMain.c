#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <math.h>       /* log() */
#include "Fraction.h"   /*fractions*/



int main(){
    fraction_t test;
    frac_init(&test,12,4);
    int pgcd = PGCD(test);
    printf("%d\n",pgcd);
    frac_print(test);
    test=frac_reduc(test);
    frac_print(test);

    
    pi1();
    pi2();
    
    
    return 0;

}