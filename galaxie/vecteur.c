#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "vecteur.h"



void vec_init(vec *v,double x,double y){
    v->x=x;
    v->y=y;
}

double norme(vec a){
    return sqrt(a.x*a.x+a.y*a.y);
}

double angle(vec a){
    return tan(a.y/a.x);
}

vec add(vec a,vec b){

    a.x+=b.x;
    a.y+=b.y;
    return a;
}
bool is_equal(vec a, vec b){
    if(a.x!=b.x)return false;
    if(a.y!=b.y)return false;
    return true;    
}

void addInPLace(vec *a, vec b){

    a->x+=b.x;
    a->y+=b.y;
}

vec sub( vec a, vec b){

    a.x-=b.x;
    a.y-=b.y;
    return a;
}

vec mult_scal( vec a, double s){

    a.x*=s;
    a.y*=s;
    return a;
}

void vec_print( vec a){
    printf("(%g,%g)\n",a.x,a.y);
    printf("norme: %g, angle: %g \n",norme(a),angle(a));
}