#ifndef _FRACTION_H_
#define _FRACTION_H_
typedef struct fraction {
	long int num;
	unsigned long long int den;
} fraction_t;

fraction_t *frac_init(long n, unsigned long long int d);
void frac_print(fraction_t *frac);
void frac_free(fraction_t *frac);
fraction_t *frac_add(fraction_t *f1, fraction_t *f2);
fraction_t *frac_add_in_place(fraction_t *f1, fraction_t *f2);
long PGCD(fraction_t *frac);
fraction_t *frac_reduc(fraction_t *f);
fraction_t *frac_pow(fraction_t *f, int pow);
fraction_t *frac_sub(fraction_t *f1, fraction_t *f2);
fraction_t *frac_mult(fraction_t *f1, fraction_t *f2);
fraction_t *frac_div(fraction_t *f1, fraction_t *f2);
fraction_t *frac_neg(fraction_t *f1);
double *frac_to_double(fraction_t *f);
fraction_t *pi1();
void pi1_wo_frac();


#endif