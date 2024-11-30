#include "tris.h"
#include <stdio.h>

bool isSorted(int size, int tab[size], bool (*comp)(int, int)){

  for( int i = 1; i<size;i++){
      if(comp(tab[i-1],tab[i])){
        printf("not sorted\n");
        return false;
      }
  }
  printf("sorted !\n");
  return true;
}

bool greater(int32_t a, int32_t b){
  return a>b;
}
bool smaller(int32_t a, int32_t b){
  return a<b;
}

void swap_value(int32_t *ind1, int32_t *ind2){
    int tmp = *ind1;
    *ind1= *ind2;
    *ind2=tmp;
}

void print_array(int32_t *arr, int32_t size){
    for(int i=0; i< size;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void arraycopy(int32_t *sorted, const int32_t *const orig,int32_t nitems){
    for(int i=0; i<nitems;i++){
        sorted[i]=orig[i];
    }
}


int partition(int size, int array[size], int first, int last,bool (*comp)(int, int)) {
  int pivot = array[last];
  int i = first;
  int j = last-1;
  while (true) {

    while (comp(array[i],pivot)){
      i++;
    } //array[i]<pivot

   while (!comp(array[j],pivot)){
      j--;
    }  //array[j]>pivot

    if (i >= j) {
      break;
    }
    //  échanger cases <i> et <j> du tableau <array>
    swap_value(&array[i], &array[j]);
  }
  // échanger cases <i> et <last> du tableau <array>
  swap_value(&array[i], &array[last]);
  return i;
}

// Tri rapide récursif
void quicksort(int size, int array[size], int first, int last,bool (*comp)(int, int)) {
  if (first < last) {
    int midpoint = partition(size, array, first, last,comp);
    if (first < midpoint - 1) {
      quicksort(size, array, first, midpoint - 1,comp);
    }
    if (midpoint + 1 < last) {
      quicksort(size, array, midpoint + 1, last,comp);
    }
  }
}

void sort(int *sorted, const int *const orig, int nitems, bool (*comp)(int, int)) {

   // copy
  for (int i = 0; i < nitems; i++) {
    sorted[i] = orig[i];
  }
  quicksort(nitems, sorted, 0, nitems-1,comp);
}