#include "matrice.h"   /*matrice*/
#include <stdio.h>
#include <math.h>
#include <limits.h>

typedef struct _pgm {
int32_t max;
matrix pixels;
} pgm;
typedef enum _pgm_error {
success, failure
} pgm_error;


pgm_error pgm_read_from_file(pgm *p, char *filename);

pgm_error pgm_write_to_file(pgm *p, char *filename);

pgm_error pgm_negative(pgm *neg, const pgm *const orig);


pgm_error pgm_symmetry_hori(pgm *sym, const pgm *const orig);

pgm_error pgm_symmetry_vert(pgm *sym, const pgm *const orig);

pgm_error pgm_symmetry_cent(pgm *sym, const pgm *const orig);

pgm_error pgm_photomaton(pgm *photomaton, const pgm *const orig);

pgm_error pgm_crop(pgm *crop, const pgm *const orig, int x0, int x1, int y0, int y1);

pgm_error pgm_conv(pgm *conv, const pgm *const orig, const matrix *const kernel);