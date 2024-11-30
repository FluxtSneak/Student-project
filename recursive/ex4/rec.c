#include "rec.h"

int count_digits(int i){
    
    if(i/10==0)return 1;
    return 1+count_digits(i/10);
}