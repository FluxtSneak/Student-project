#include <stdlib.h>
#include "hash.h"
#include <stdio.h>


int main(){
    hm_t *hm = hm_create(7);

    for(int i=0;i<15;i++){
    char str1[80];
    char str2[80];
    sprintf(str1,"%d", i);
    sprintf(str2,"%d", i*10);
    hm_set(hm,str1,str2);
    // hm_rm(hm,str1);
  }

  hm_print(hm);
  printf("\nget (1 - %s)\n",hm_get(hm,"1"));
  printf("get (8 - %s)\n\n",hm_get(hm,"8"));

  hm_print(hm);
  
  hm_print(hm);
  hm_destroy(&hm);



    return 0;
}