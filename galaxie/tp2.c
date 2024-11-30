#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tp2.h"

#define G 6.673e-11

error_code create_particule ( particule *p, double m, double x, double y){
    p->masse=m;
    vec_init(&p->pos,x,y);
    vec_init(&p->last_pos,-1,-1);
    vec_init(&p->forces,0.00,0.00);
    return ok;
}

error_code fill_tab_with_particules(particule tab[],int size){
    srand (time(NULL));
    particule p;    
    for(int i=0;i<size;i++){
        create_particule(&p, ((double)rand()/RAND_MAX)*10, ((double)rand()/RAND_MAX)*10, ((double)rand()/RAND_MAX)*10);
        tab[i]=p;
    }
    return ok;
}
error_code galaxy_init(galaxy *sys,particule tab[],int size, int height, int width){
    fill_tab_with_particules(tab,size);
    sys->tab=tab;
    create_particule(&sys->blackhole, 1000000.000, (double)height/2, (double)width/2);
    sys->size=size;
    sys->height=height;
    sys->width=width;
    force_res(sys);
    speed(sys);
    return ok;
}
vec attraction_force(particule a, particule b) {
  vec Rij = sub(a.pos, b.pos);
  return mult_scal(Rij, -G * ((a.masse * b.masse) / (pow(norme(Rij), 3))));
}
error_code force_res(galaxy *sys){
    for (int i = 0; i < sys->size; i++) {
    for (int j = 0; j < sys->size; j++) {
      if (j != i) {
        sys->tab[i].forces = add(sys->tab[i].forces,attraction_force(sys->tab[i], sys->tab[j]));
      }
    }
    sys->tab[i].forces = add(sys->tab[i].forces,attraction_force(sys->tab[i], sys->blackhole));
  }
    return ok;
}
error_code vitesse_frot(particule tab[], int size, double k){
    for(int i = 0; i < size; i++){
        tab[i].forces=add(mult_scal(tab[i].vitesse,k),tab[i].forces);
    }
    return ok;
}

error_code transition(galaxy *sys, double dt){
    for(int i=0;i<sys->size;i++){
    vec fAttra = attraction_force(sys->tab[i], sys->blackhole);
    vec aCent = mult_scal(fAttra, 1 / sys->tab[i].masse);

    if (sys->tab[i].last_pos.x == -1 && sys->tab[i].last_pos.y == -1) { // first iteration
      sys->tab[i].last_pos = sys->tab[i].pos;
      sys->tab[i].pos = add(add(sys->tab[i].pos, mult_scal(sys->tab[i].vitesse, dt)), mult_scal(aCent, dt * dt));

    } else { // then
      vec nextPos = add(sub(mult_scal(sys->tab[i].pos, 2), sys->tab[i].last_pos), mult_scal(aCent, dt * dt));
      sys->tab[i].last_pos = sys->tab[i].pos;
      sys->tab[i].pos = nextPos;
    }
    }
    check_pos(sys);
    return ok;
}
error_code check_pos(galaxy *g){
    for(int i=0; i<g->size;i++){
        if(g->tab[i].pos.x>10)g->tab[i].pos.x-=10;
        if(g->tab[i].pos.y>10)g->tab[i].pos.y-=10;
        if(g->tab[i].pos.x<0)g->tab[i].pos.x+=10;
        if(g->tab[i].pos.y<0)g->tab[i].pos.y+=10;
    }
    return ok;
}
vec closest_path(particule a, particule b, int height, int width){
    int x = b.pos.x;
    int y= b.pos.y;
    if(a.pos.x-b.pos.x>height/2 ||  b.pos.x-a.pos.x>height/2){
        x=b.pos.x+10;
    }
    if(a.pos.y-b.pos.y>width/2 ||  b.pos.y-a.pos.y>width/2){
        y=b.pos.y+10;
    }
    vec close;
    vec_init(&close, x, y);
    return close;
}
error_code speed(galaxy *sys){
  for (int i = 0; i < sys->size; i++) {
    vec r = sub(sys->tab[i].pos, sys->blackhole.pos);
    double v = sqrt((G * sys->blackhole.masse) / norme(r));
    // normalize and rotate 90 deg
    vec n = r;
    n.x = -r.y / norme(r);
    n.y = r.x / norme(r);
    // scale length
    sys->tab[i].vitesse = mult_scal(n, v);
  }
  return ok;
}
