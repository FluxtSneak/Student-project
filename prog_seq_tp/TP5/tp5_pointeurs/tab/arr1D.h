#ifndef _ARR1D_H_
#define _ARR1D_H_

#include <stdint.h>
#include <stdbool.h>

void arr2d_init(int height, int width, int **histo_2d);

void randomFill2D(int height, int width, int **arr2d);

void display2D(int height, int width, int **arr2d);


void histo(int size, int arr[],int histo[]);

void randomFill(int size, int arr[]);

void printArr(int size, int arr[]);

 int findSmallest(int size, int arr[]);

  int findBigest(int size, int arr[]);


 void checkEquity(int size, int arr[]);


  void swapArr(int arr[],int i,int j);


void bigToEnd(int size, int arr[]);


 int seekElement(int size, int arr[],int el);

 double average(int size,int arr[]);
 

 double variance(int size,int arr[]);

 void sort(int size,int arr[]);


 double findMedian(int size,int arr[]);

 

#endif
