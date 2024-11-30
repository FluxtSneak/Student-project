#include "rec.h"

int sum(int i, int *tab){    
    i-=1;
    if(i <1)return tab[0];
    return tab[i]+sum(i,tab);
}