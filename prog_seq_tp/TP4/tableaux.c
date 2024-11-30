#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <math.h>       /* log() */
#include <time.h>       /* time() */
#include "tableaux.h"   /*tableaux*/


void fill_with_rand(int size, int tab[size]){
    srand(time(NULL));

    for (int i=0; i<size; i++){
        tab[i]=rand()%size;
    }
}
int find_smallest(int size, int tab[size]){
    int a=tab[0];
    for (int i =0;i<size;i++){
        if(tab[i]<a){
            a=tab[i];
        }
    }
    return a;
}
void swap_big_at_end(int size, int tab[size]){
    int tmp=0;
    int max=tab[0];
    for (int i=0; i<size;i++){
        if(tab[i]>max){
            max=tab[i];
            tmp=i;
        }
    }
    int tabmax=tab[size];
    tab[size]=max;
    tab[tmp]=tabmax;

}
void swap(int size, int tab[size], int ind1, int ind2){
    int a=tab[ind1];
    tab[ind1]=tab[ind2];
    tab[ind2]=a;

}
int find(int size, int tab[size],int nb){
    
    for(int i=0;i<size;i++){
        if (tab[i]==nb){
            return i;
        }
    }
    printf("La valeur n'existe pas dans le tableau \n");
    return -1;    
}
double average(int size, int tab[size]){
    double a =0;
    for (int i=0;i<size;i++){
        a+=tab[i];
    }
    return a/=size;
}
double variance(int size, int tab[size]){
    double tmp;
    double a;
    double moy = average(size, tab);
    for (int i=0;i<size;i++){
        tmp=tab[i]-moy;
        tmp*=tmp;
        a+=tmp;
    }
    return a/=size;

}
void sort(int size, int tab[size]){
    int j;
    for(int i=0;i<size;i++){
        j=i=tab[j];
        for (int k=i+1;k<size;k++){
        if(tab[k]<tab[j]){
            j=k;
        }
        swap(size, tab, i,j);
        j++;
    }
    
    

    }
    
}
double find_median(int size, int tab[size]){
    if(size%2){
        return tab[(size-1)/2];
    }
    else{
        return (tab[(size-1)/2]+tab[size/2])/2.0;
    }
}
void show(int size, int tab[size]){
    for (int i=0;i<size;i++){
        printf("%d " ,tab[i]);
    }
    printf("\n");
    
}
void init(int size, int tab[size]){
    for (int i=0;i<size;i++){
        tab[i]=0;
    }
}
void check_tabs(int size ,int tab[size], int size2, int tab2[size2]){
    for(int i=0;i<size2; i++){
        for (int j=0;j<size;j++){
            if(tab[j]==i){
                tab2[i]+=1;
            }
        }
    }
}
