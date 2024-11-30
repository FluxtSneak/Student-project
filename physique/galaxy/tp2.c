#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tp2.h"

#define G 6.673e-11

error_code create_particule ( particule *p, double m, double x, double y){
    p->masse=m;
    vec_init(&p->pos,x,y);
    vec_init(&p->last_pos,x,y);
    vec_init(&p->forces,0.00,0.00);
    vec_init(&p->force_BH, 0, 0);
    vec_init(&p->vitesse, 0, 0);
    return ok;
}

error_code fill_tab_with_particules(particule tab[],int size){
    srand (time(NULL));
    particule p;    
    for(int i=0;i<size;i++){
        create_particule(&p, ((double)rand()/RAND_MAX)*10, ((double)rand()/RAND_MAX)*10, ((double)rand()/RAND_MAX)*10);
        tab[i]=p;
        printf("particule nb : %d, masse = %f, x = %f et y = %f\n\n",i, tab[i].masse, tab[i].pos.x,tab[i].pos.y);
    }
    return ok;
}
error_code galaxy_init(galaxy *sys,int size, int height, int width){
    //sys->tab=tab;
    //create_particule(&(sys->blackhole), 1000.000, (double)height/2, (double)width/2);
    sys->size=size;
    sys->height=height;
    sys->width=width;
    //fill_tab_with_particules(sys->tab,size);
    //speed(sys);
    //force_res(sys);
    //vitesse_frot(tab, size, -10.00);
    return ok;
}
error_code force_res(galaxy *sys){
    for(int i = 0; i < sys->size; i++){
        vec fi;
        double scal;
        for(int j = 0; j < sys->size; j++){
            vec close=closest_path(sys->tab[i], sys->tab[j],sys->height, sys->width);
            if(j!=i){
                fi=sub(sys->tab[i].pos,close);
                scal=(6.67*pow(10,-11))*(sys->tab[i].masse*sys->tab[j].masse/(pow(norme(fi),3)));
                sys->tab[i].forces= add(mult_scal(fi,scal),sys->tab[i].forces);
                if(j==sys->size && is_equal(sys->tab[i].vitesse, sys->tab[i].force_BH)){
                    vec un = mult_scal(fi, scal);
                    vec_print(un);
                    vec_print(fi);
                    sys->tab[i].force_BH=mult_scal(fi, scal);
                    vec_print(sys->tab[i].force_BH);
                    printf("ok\n");
                }
            }
        }
        //calculate the same, for the blackhole
        vec close = closest_path(sys->tab[i], sys->blackhole,sys->height, sys->width);
        fi=sub(sys->tab[i].pos,close);
        scal=(6.67*pow(10,-11))*(sys->tab[i].masse*sys->blackhole.masse/(pow(norme(fi),3)));
        sys->tab[i].force_BH=mult_scal(fi,scal);
        sys->tab[i].forces= add(mult_scal(fi,scal),sys->tab[i].forces);



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

    vec a;

    for(int i=0; i<sys->size; i++){
        force_res(sys);    
        a = mult_scal(sys->tab[i].forces, -1/sys->tab[i].masse);
        if(is_equal(sys->tab[i].pos, sys->tab[i].last_pos)){
            sys->tab[i].pos=add(add(sys->tab[i].pos, mult_scal(sys->tab[i].vitesse, dt)),mult_scal(a, dt*dt));
            printf("force bh x = %g  y = %g \n ",sys->tab[i].force_BH.x,sys->tab[i].force_BH.y );
        }
        else{
            sys->tab[i].last_pos=sys->tab[i].pos;
            sys->tab[i].pos=add(sub(mult_scal(sys->tab[i].pos,2),sys->tab[i].last_pos),mult_scal(a, dt*dt));            
            sys->tab[i].vitesse=mult_scal(sub(sys->tab[i].pos, sys->tab[i].last_pos), 1 / dt);
            //printf("force bh x = %g  y = %g \n ",sys->tab[i].force_BH.x,sys->tab[i].force_BH.y );
                         
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
