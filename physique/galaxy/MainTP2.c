#include <stdio.h>      /* printf(), scanf() */
#include <stdlib.h>
#include <time.h> 
#include <math.h>       /* log() */
#include "tp2.h"
#include "gfx.h"
#include <unistd.h>

static void render(struct gfx_context_t *context, galaxy sys) {
	gfx_clear(context, COLOR_BLACK);
    
    uint32_t intensity = 255;
    uint32_t color=MAKE_COLOR(intensity,intensity,intensity);
    for (int i =0; i<sys.size; i++){
        int x= (int)(sys.tab[i].pos.x*100);
        int y= (int)(sys.tab[i].pos.y*100);
        //printf("x = %d  et y = %d\n", x ,y);
        gfx_putpixel(context,x,y,color);   
    }
    //put blackhole in red
    color=MAKE_COLOR(255,0,0);
    gfx_putpixel(context,sys.blackhole.pos.x*100, sys.blackhole.pos.y*100, color);
	
}

int main(){

    int width = 1000, height = 1000;
    int size =10;
    //particule tab[size];
    galaxy my_galaxy;
    galaxy_init(&my_galaxy, size, 10, 10);
    
    double deltaT= 5;
    struct gfx_context_t *ctxt = gfx_create("tst", width, height);
    

    if (!ctxt) {
		fprintf(stderr, "Graphics initialization failed!\n");
		
	}
    
    while (gfx_keypressed() != SDLK_ESCAPE) {
        //render(ctxt, my_galaxy);
        //transition(&my_galaxy, deltaT);
		gfx_present(ctxt);
	}
	gfx_destroy(ctxt);
      
    
	


    return 0;
}
