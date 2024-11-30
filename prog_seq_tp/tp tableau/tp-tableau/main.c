#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>     /* srand(), rand() */
#include <time.h>       /* time() */
#include <math.h>       /* log() */
#include "tableaux.h"   /*tableaux*/
#include "gfx.h"

static void render(struct gfx_context_t *context, int tab[], int size) {
	gfx_clear(context, COLOR_BLACK);
    
    uint32_t intensity = 255;
    uint32_t color=MAKE_COLOR(intensity,intensity,intensity);
    for (int i =0; i<size; i++){
        for (int j=0;j<tab[i];j++){
            gfx_putpixel(context,i+10,j,color);
        }
        
    }
	
}

int main(){
    int size;

    printf ("Entrez un nombre strictement positif afin de définir la taille de votre tableau \n");
    scanf("%d", &size);
    int tab[size];
    fill_with_rand(size, tab);
    show(size, tab);
    int smallest_value=find_smallest(size, tab);
    printf("La plus petite valeur du tableau est : %d \n", smallest_value);
    swap_big_at_end(size, tab);
    printf("Entrez une valeur à rechercher dans le tableau :\n");
    int looked;
    scanf("%d", &looked);    
    int ind_looked = find(size, tab, looked)+1;
    printf("La valeur se trouve en : %d \n", ind_looked);
    double av= average(size, tab);
    printf("Moyenne : %f \n", av);
    double var=variance(size, tab);
    printf("Variance : %f \n", var);
    sort(size, tab);    
    double med =find_median(size, tab);
    printf("Medianne : %f \n", med);
    show(size, tab);
    int tab_check[size];
    init(size, tab_check);
    check_tabs(size, tab, size, tab_check);
    show(size, tab_check);
 
    int width = 800, height = 600;
	struct gfx_context_t *ctxt = gfx_create("Example", width, height);
	if (!ctxt) {
		fprintf(stderr, "Graphics initialization failed!\n");
		return EXIT_FAILURE;
	}

	while (gfx_keypressed() != SDLK_ESCAPE) {
		render(ctxt, tab_check, size);
		gfx_present(ctxt);
	}

	gfx_destroy(ctxt);
	return EXIT_SUCCESS;


return 0;
}
