#include "rec.h"

int main(){
    assert(is_sum_digits("ABBA",0,3)==true);
    assert(is_sum_digits("albuchef",0,7)==false);
    printf("Tests are ok\n");
}