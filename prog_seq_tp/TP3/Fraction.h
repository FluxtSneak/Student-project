#ifndef _FRACTION_H_
#define _FRACTION_H_
typedef struct fraction {
	int den;
	int num;
} fraction_t;

void frac_init(fraction_t *frac, int num, int den);
void frac_print(fraction_t frac);
int PGCD(fraction_t frac);
fraction_t frac_reduc(fraction_t frac);
fraction_t frac_pow(fraction_t frac, int puiss);
fraction_t frac_add(fraction_t frac1, fraction_t frac2);
fraction_t frac_sub(fraction_t frac1, fraction_t frac2);
fraction_t frac_mult(fraction_t frac1, fraction_t frac2);
fraction_t frac_div(fraction_t frac1, fraction_t frac2);
fraction_t frac_neg(fraction_t frac);
double frac_to_double(fraction_t frac);
void pi1();
void pi2();
void pi3();



#endif