
#include "arr1D.h"
#include "gfx.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void render2d(struct gfx_context_t *context, int **histo_2d, int size) {
  gfx_clear(context, COLOR_WHITE);

  uint color1; 
  int color;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      color=histo_2d[i][j]*10;
      
      color1= MAKE_COLOR(color, color, color);
      gfx_putpixel(context, i + 10, j, color1);
    }
  }
}
static void render(struct gfx_context_t *context, int tab[], int size) {
  gfx_clear(context, COLOR_BLACK);

  uint color = MAKE_COLOR(255, 255, 255);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < tab[i]; j++) {
      gfx_putpixel(context, i + 10, j, color);
    }
  }
}
int main() {

  int size;
  // 1
  printf("enter size\n");
  scanf("%d", &size);

  int *arr = malloc(size * sizeof(int));

  // 2
  // int arr[size];
  randomFill(size, arr);
  printArr(size, arr);
  // 3
  findSmallest(size, arr);
  // 4
  // bigToEnd(size, arr);
  printArr(size, arr);
  // 5
  printf("enter element to seek\n");
  int el;
  scanf("%d", &el);
  seekElement(size, arr, el);
  // 6
  average(size, arr);
  // 7
  variance(size, arr);
  // 8
  sort(size, arr);
  printArr(size, arr);
  // 9
  printf("median= %f\n", findMedian(size, arr));
  // 11
  checkEquity(size, arr);
  // 12
  int counter[size + 1];

  for (int i = 0; i < size + 1; ++i) {
    counter[i] = 0;
  }
  // 4.1 plus supplémentaire
  int height = 500;
  int width = 500;

  // ____________width
  // |
  // |
  // |
  // |
  // height

int **histo2d= malloc(height * sizeof(int *));

 for (int i = 0; i < height; i++) {
    histo2d[i] = malloc(width * sizeof(int));
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      histo2d[i][j] = 0;
    }
  };


  // arr2d_init(height,width,histo2d);
  randomFill2D(height,width, histo2d);
  display2D(height,  width, histo2d);





  histo(size, arr, counter);
  printArr(size, counter);
  free(arr);


  struct gfx_context_t *ctxt = gfx_create("Example", 800, 600);
  if (!ctxt) {
    fprintf(stderr, "Graphics initialization failed!\n");
    return EXIT_FAILURE;
  }

  while (gfx_keypressed() != SDLK_ESCAPE) {
    render2d(ctxt, histo2d, height);
    gfx_present(ctxt);
  }

  gfx_destroy(ctxt);
  return EXIT_SUCCESS;

for (int i = 0; i < width; i++) {
  free(histo2d[i]);
  }
free(histo2d);
}
