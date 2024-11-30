#include "arr1D.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void arr2d_init(int height, int width, int **histo_2d) {

 *histo_2d= malloc(height * sizeof(int *));

  for (int i = 0; i < height; i++) {
    histo_2d[i] = malloc(width * sizeof(int));
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      histo_2d[i][j] = 0;
    }
  }
}

void randomFill2D(int height, int width, int **arr2d) {

 

  
  for (int i = 0; i < height*width; i++) {
    int r1 = rand() % (height);
    int r2 = rand() % (width);
    arr2d[r1][r2]++;
  }
}

void display2D(int height, int width, int **arr2d) {
  for (int i = 0; i < height; i++) {
    printf("\n");
    for (int j = 0; j < width; j++) {
      printf("%d ",arr2d[i][j]);
    
    }
  }
  printf("\n");
}

void randomFill(int size, int arr[]) {
  srand(time(NULL));

  for (int i = 0; i < size; ++i) {

    arr[i] = rand() % (size);
  }
}

void printArr(int size, int arr[]) {

  for (int i = 0; i < size; ++i) {

    printf("[%d]= %d \n", i, arr[i]);
  }
}

int findSmallest(int size, int arr[]) {

  int s = arr[0];

  for (int i = 1; i < size; ++i) {

    if (arr[i] < s) {
      s = arr[i];
    }
  }
  printf("smallest : %d\n", s);
  return s;
}

int findBigest(int size, int arr[]) {

  int s = arr[0];

  for (int i = 1; i < size; ++i) {

    if (arr[i] > s) {
      s = arr[i];
    }
  }
  return s;
}

void checkEquity(int size, int arr[]) {

  // printArr(size, arr);

  int max = findBigest(size, arr) + 1;
  int histo[max];

  for (int i = 0; i < max; ++i) {
    histo[i] = 0;
  }

  // count each
  for (int i = 0; i < size; ++i) {

    histo[arr[i]]++;
  }

  for (int i = 0; i < max; i++) {
    printf("nb de [%d]= %d \n", i, histo[i]);
  }
  // even if average=size/2
}

void histo(int size, int arr[], int histo[]) {

  // count each
  for (int i = 0; i < size - 1; ++i) {
    histo[arr[i]]++;
  }
}

void swapArr(int arr[], int i, int j) {
  int tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

void bigToEnd(int size, int arr[]) {

  int b = arr[0];
  int index = 0;

  for (int i = 1; i < size; ++i) {

    if (arr[i] > b) {
      b = arr[i];
      index = i;
    }
  }

  swapArr(arr, index, size);
}

int seekElement(int size, int arr[], int el) {

  int r = -1;
  for (int i = 0; i < size; ++i) {

    if (arr[i] == el) {
      r = i;
      break;
    }
  }

  if (r == -1) {
    printf("%d is not in the array", el);
  } else {

    printf("%d is at index %d\n", el, r);
  }
  return r;
}

double average(int size, int arr[]) {

  double sum = 0.0;

  for (int i = 0; i < size; ++i) {
    sum += arr[i];
  }
  printf("average : %f\n", sum / size);
  return sum / size;
}

double variance(int size, int arr[]) {

  double m = average(size, arr);
  double v = 0;
  for (int i = 0; i < size; ++i) {
    v += (arr[i] - m) * (arr[i] - m);
  }
  printf("variance= %f\n", v / size);
  return v / size;
}

void sort(int size, int arr[]) {

  int i_min;

  for (int i = 1; i < size; i++) {
    i_min = i;

    for (int k = i + 1; k < size; k++) {
      if (arr[k] < arr[i_min]) {
        i_min = k;
      }
    }
    swapArr(arr, i, i_min);
  }
}

double findMedian(int size, int arr[]) {

  sort(size, arr);

  if (size % 2) { // odd
    return arr[(size - 1) / 2];

  } else { // even
    return (arr[(size - 1) / 2] + arr[size / 2]) / 2.0;
  }
}
