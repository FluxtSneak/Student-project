#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <math.h>       /* log() */
#include "Fraction.h"   /*fractions*/

void frac_init(fraction_t *frac, int num, int den){
    if (den==0){
        printf("erreur le dénominateur ne peut pas être 0 !");
        exit(EXIT_FAILURE);
    }
	frac->num=num;
	frac->den=den;
}
void frac_print(fraction_t frac){
    printf("%d / %d\n", frac.num, frac.den);
}
int PGCD(fraction_t frac){
    int a = frac.num;
    int b = frac.den;
    int t;
    while(b!=0){
        t=b;
        b= a%b;
        a=t;
    }
    return a;
}
fraction_t frac_reduc(fraction_t frac){
    int pgcd=PGCD(frac);
    frac.num /= pgcd;
    frac.den /= pgcd;
    return frac;

}
fraction_t frac_pow(fraction_t frac, int puiss){
    frac.num = pow(frac.num,puiss);
    frac.den =pow(frac.den,puiss);
    return frac_reduc(frac);
}
fraction_t frac_add(fraction_t frac1, fraction_t frac2){
    frac1.num*=frac2.den;
    frac2.num*=frac1.den;
    frac1.den*=frac2.den;
    frac2.den=frac1.den;
    frac1.num+=frac2.num;
    frac1= frac_reduc(frac1);
    return frac1;
}

fraction_t frac_sub(fraction_t frac1, fraction_t frac2){
    frac1.num*=frac2.den;
    frac2.num*=frac1.den;
    frac1.den*=frac2.den;
    frac2.den=frac1.den;
    frac1.num-=frac2.num;
    frac1=frac_reduc(frac1);
    return frac1;
}
fraction_t frac_mult(fraction_t frac1, fraction_t frac2){
    frac1.num*=frac2.num;
    frac1.den*=frac2.den;    
    return frac_reduc(frac1);
}
fraction_t frac_div(fraction_t frac1, fraction_t frac2){
    frac1.num*=frac2.den;
    frac1.den*=frac2.num;    
    return frac_reduc(frac1);
}
fraction_t frac_neg(fraction_t frac){
    frac.num *=-1;
    return frac;
}
double frac_to_double(fraction_t frac){
    double a = frac.num/frac.den;
    return a;
}
void pi1(){
    double pi;
    fraction_t f1,res;
    frac_init(&f1, 1,1);
    frac_init(&res,0,1);
    for(int i=1; i<6;i++){
        f1.den=pow(i,4);
        res=frac_add(f1,res);  
        frac_print(res);      
    }
    pi=pow(res.num/(res.den/90),0.25);
    printf("pi =~ %lf \n", pi);

}
void pi2(){
    fraction_t f1,res;
    frac_init(&f1, 1,1);
    frac_init(&res, 1,4);
    res=frac_sub(f1,res);
    for(int i=3; i<10;i++){
        f1.num=pow((-1),i+1);
        f1.den=i*i;
        res=frac_add(f1,res);
        frac_print(res);
    }
    double pi =pow(res.num/(res.den/12),0.5);
    printf("pi =~ %lf \n", pi);
}
void pi3(){
    double pi4;
    fraction_t f1,f2;
    frac_init(&f1, 1,1);
    frac_init(&f2,1,1);
    for(int i=2; i<10;i++){
        f2.den=pow(i,4);
        f1=frac_add(f1,f2);
        pi4=pow(f1.num,0.25);
        printf("pi est environ : %f \n", pi4);
    }

}
