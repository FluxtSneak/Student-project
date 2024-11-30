#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>     /* srand(), rand() */
#include <time.h>       /* time() */
#include <math.h>       /* log() */
#include <stdbool.h>    /*bool */

double function_g(double x);
bool check_precision(double e);
bool check_interval(double a, double b);
void find_interval(double a, double b, double e);
int32_t bissect(double a1, double b1, double epsilon,double *z);

int main(){
    double a;
    double b;
    double e;    
    double zero1;
    int32_t it;

    printf("Enter the desire interval ( point 'a', point 'b') ");
    scanf("%lf %lf" , &a ,&b);
    while(!check_interval(a,b)){
        printf("Can't calculate with the interval given, please change them ");
        scanf("%lf %lf" , &a ,&b);
    }
    
    printf("enter the desired precision level");
    scanf("%lf", &e);
    while (!check_precision(e)){
        printf("Can't calculate to the precision level given, please change it ");
        scanf("%lf" , &e);
    }
    it = bissect(a,b,e,&zero1);
    printf("Le zero est %lf \n Trouvé en %d itérations",zero1, it);
    
    return EXIT_SUCCESS;

}

double function_g(double x){
return pow(x,4)+pow(x,3)+pow(x,2)-1;
}
bool check_precision(double e){
    return e>=0.00000001;
}

bool check_interval(double a, double b){
    return function_g(a)*function_g(b)<0;
}
int32_t bissect(double a1, double b1, double epsilon, double *z){
    double c;
    int32_t i = 0;
    while ((b1-a1)>epsilon){
        i++;
        c=(a1+b1)/2;
        if(function_g(a1)*function_g(c)>0){
            a1=c;
        } 
        else{
            b1=c;
        }
    }
    *z=(a1+b1)/2;
    return i;
}



