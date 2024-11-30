#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <math.h>       /* log() */
#include "Fraction.h"   /*fractions*/

fraction_t *frac_init(long num, unsigned long long int den){
    fraction_t *f = (fraction_t*)malloc(sizeof(fraction_t));
	f->num=num;
    if (den==0){
        printf("erreur le dénominateur ne peut pas être 0 ! setted to 1\n");
        f->den =1;
    }
    else {
	f->den=den;
    }
    return f;
}
void frac_print(fraction_t *frac){
    printf("%ld / %lld\n", frac->num, frac->den);
}
void frac_free(fraction_t *frac){
    free(frac);
}
fraction_t *frac_add(fraction_t *f1, fraction_t *f2){
    fraction_t *f=frac_init((f1->num*f2->den)+(f2->num*f1->den),f1->den*f2->den);
    return frac_reduc(f);
}
fraction_t *frac_add_in_place(fraction_t *f1, fraction_t *f2){
    fraction_t *f;
    if(f1->den%f2->den==0){
        if(f1->den>f2->den){
            f=frac_init(f1->num+(f2->num*(f1->den/f2->den)),f1->den);
        }
        else{
            f=frac_init(f2->num+(f1->num*(f2->den/f1->den)),f2->den);
        }
    }   
    else{
        f=frac_init((f1->num*f2->den)+(f2->num*f1->den),f1->den*f2->den);
    }
    
    free(f2);
    return frac_reduc(f);
}
long PGCD(fraction_t *frac){
    long a = frac->num;
    unsigned long long int b = frac->den;
    long t;
    while(b!=0){
        t=b;
        b= a%b;
        a=t;
    }
    return a;
}
fraction_t *frac_reduc(fraction_t *f){
    long pgcd = PGCD(f);
    
    f->num/=pgcd;
    f->den/=pgcd;
    return f;
}
fraction_t *frac_pow(fraction_t *f, int power){
    f->num=pow(f->num,power);
    f->den=pow(f->den,power);
    f=frac_reduc(f);
    return f;
}
fraction_t *frac_sub(fraction_t *f1, fraction_t *f2){
    fraction_t *f=frac_init((f1->num*f2->den)-(f2->num*f1->den),f1->den*f2->den);
    return frac_reduc(f);
}
fraction_t *frac_mult(fraction_t *f1, fraction_t *f2){
    fraction_t *f=(fraction_t*)malloc(sizeof(fraction_t));
    f->num=f1->num*f2->num;
    f->den=f1->den*f2->den;
    return frac_reduc(f);
}
fraction_t *frac_div(fraction_t *f1, fraction_t *f2){
    fraction_t *f = frac_init(f1->num*f2->den,f1->den*f2->num);  
    return frac_reduc(f);
}
fraction_t *frac_neg(fraction_t *f1){
    fraction_t *f=frac_init(f1->num*(-1),f1->den);    
    return frac_reduc(f);    
}
double *frac_to_double(fraction_t *f){
    double *d=(double*)malloc(sizeof(double));
    *d = f->num/f->den;
    return d;
}
fraction_t *pi1(){
    fraction_t *f1=frac_init(1,1);
    fraction_t *res=frac_init(0,1);

    for(int i =1 ; i<12;i++){
        f1->den=pow(i,4);
        //printf("f1 = ");
        //frac_print(f1);
        res = frac_add_in_place(f1,res);
        printf("res = ");
        frac_print(res);
        //printf(" pi ~= %lf \n", pow(res->num,0.25)/90);


    }
    long double a = pow(res->num/(res->den/90),0.25);
    printf("pi= %Lf\n",a);
    free(f1);
    return res;

}
void pi1_wo_frac(){
    double pi;

    for(int i=1;i<100;i++){
        pi+=1/pow(i,4);
        
    }
    pi*=90;
    pi=pow(pi,0.25);
    printf("pi= %lf", pi);
}