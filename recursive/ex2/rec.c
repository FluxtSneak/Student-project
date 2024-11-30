#include "rec.h"

int sum(int i){    
    if(i <1)return 0;
    return i+sum(i-1);
}