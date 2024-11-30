#include "rec.h"

bool is_sum_digits(char*mot,int ind, int last){
    
    if(mot[ind]==mot[last]){
        if(ind>last)return true;
        ind++;
        last--;
        return is_sum_digits(mot, ind, last);
    };
    return false;
    
    
}