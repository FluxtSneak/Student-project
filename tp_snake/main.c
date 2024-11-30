#include "gfx.h"
#include "snake.h"
#include <SDL2/SDL_keycode.h>
#include <stdlib.h>
#include <unistd.h>


static void render(struct gfx_context_t *ctxt, snake *snk,int width, int height) {
    
	move(snk,ctxt);
	if(!snk->isAlive){		
		gfx_clear(ctxt, COLOR_BLACK);
		initGame(snk, ctxt, width, height);		
	}
	if(snk->foodAct<10)createFood(ctxt, snk, width, height);
	usleep(23000);
	
}



int main(){
    int width = 240, height = 135;
    snake snk;
    struct gfx_context_t *ctxt = gfx_create("Snayyyke", width, height);
	initGame(&snk, ctxt, width, height);
	if (!ctxt) {
		fprintf(stderr, "Graphics initialization failed!\n");		
	}
	SDL_Keycode key;
	while (key != SDLK_ESCAPE) {
		key=gfx_keypressed();
		changedirection(&snk, key);		
		render(ctxt, &snk,width,height);
        gfx_present(ctxt);
	}
	gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}