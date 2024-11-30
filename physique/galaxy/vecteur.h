#include <stdbool.h>
typedef struct _vec{
    double x;
    double y;
} vec;
void vec_init(vec *v,double x,double y);
double norme(vec a);
double angle(vec a);
vec add(vec a, vec b);
bool is_equal(vec a, vec b);
void addInPLace( vec *a, vec b);
vec sub(vec a,vec b);
vec mult_scal(vec a,double s);
void vec_print(vec a);