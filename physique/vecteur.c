#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct vec{
    double x;
    double y;
};

void vec_init(struct vec *v,double x,double y){
    v->x=x;
    v->y=y;
}

double norme(struct vec a){
    return sqrt(a.x*a.x+a.y*a.y);
}

double angle(struct vec a){
    return tan(a.y/a.x);
}

struct vec add(struct vec a,struct vec b){

    a.x+=b.x;
    a.y+=b.y;
    return a;
}

void addInPLace(struct vec *a,struct vec b){

    a->x+=b.x;
    a->y+=b.y;
}

struct vec sub(struct vec a,struct vec b){

    a.x-=b.x;
    a.y-=b.y;
    return a;
}

struct vec mult_Scal(struct vec a,double s){

    a.x*=s;
    a.y*=s;
    return a;
}

void print(struct vec a){
    printf("(%.2f,%.2f)\n",a.x,a.y);
    printf("norme: %.2f, angle: %.2f \n",norme(a),angle(a));
}



void main(){

struct vec v1;
struct vec v2;
vec_init(&v1,1,2);
vec_init(&v2,4,3);
print(v1);
print(v2);
addInPLace(&v1,v2);
print(v1);
print(v2);

// v1.x=2;
// v1.y=3;
// struct vec v2=v1;
// v2.x=4;

// print(v1);
// print(v2);

// struct vec v3=add(v1,v2);
// print(v3);

// addInPLace(&v1,v2);
// print(v1);








}