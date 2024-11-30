#include "rec.h"

int sum_digits(int i){
    
    if(i/10==0)return i;
    int r=i%10;
    i/=10;
    return r+sum_digits(i);
}