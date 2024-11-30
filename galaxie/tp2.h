#include "vecteur.h"

typedef enum _error_code {
ok,
out_of_bounds, 
memory_error, 
overflow, 
uninitialized
}error_code;

typedef struct _particule {
    double masse;
    vec pos;
    vec last_pos;
    vec forces;
    vec force_BH;
    vec vitesse;
} particule;

typedef struct _galaxy {
    particule *tab;
    particule blackhole;
    int size;
    int height;
    int width;
} galaxy;
error_code galaxy_init(galaxy *sys, particule tab[],int size, int height, int width);
error_code create_particule( particule *p, double m, double x, double y);
vec attraction_force(particule a, particule b);
error_code fill_tab_with_particules(particule tab[],int size);
error_code force_res(galaxy *sys);
error_code transition(galaxy *sys, double dt);
error_code vitesse_frot(particule tab[], int size, double k);
error_code check_pos(galaxy *g);
vec closest_path(particule a, particule b, int height, int width);
error_code speed(galaxy *sys);