#ifndef _FRACTION_H_
#define _FRACTION_H_
typedef struct fraction {
	int den;
	int num;
} fraction_t;

fraction_t *frac_init(long n, long d);
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


#endif