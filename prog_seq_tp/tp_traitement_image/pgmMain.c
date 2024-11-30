#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "pgm.h"
#include "gfx.h"


static void render(struct gfx_context_t *context, pgm my_pgm) {
	gfx_clear(context, COLOR_BLACK);
    for (int i =0; i<my_pgm.pixels.m; i++){
        for(int j=0; j<my_pgm.pixels.n; j++){        
            uint32_t intensity = (uint32_t)my_pgm.pixels.data[i][j];
            uint32_t color=MAKE_COLOR(intensity,intensity,intensity);
            gfx_putpixel(context,j,i,color);
        }    
    }
}

int main(){
    //declare filters as array
    int filter_blur[]={1,1,1,1,1,1,1,1,1};
    int filter_sharp_edge[]={0,-1,0,-1,5,-1,0,-1,0};
    int filter_box_blur[]={1,2,1,2,4,2,1,2,1};
    int filter_unsharp[]={-1,-4,-6,-4,-1,-4,-16,-4,-16,-4,-6,-24,476,-24,-6,-4,-16,-24,-16,-4,-1,-4,-6,-4,-1};
    //make a matrix for a kernel
    matrix kernel;
    matrix_init_from_array(&kernel, 5,5,filter_unsharp);

    //declare variables to store pgm after treatment
    pgm my_pgm;
    pgm negative;
    pgm sym_h;
    pgm sym_v;
    pgm sym_c;
    pgm photo;
    pgm crop;
    pgm conv;
    char name[80];

    //asking user the name of the image to use
    
    printf("Please, enter the name of your image. \n");
    scanf("%s",name); 
      

    
    assert( pgm_read_from_file(&my_pgm, name) != failure);

    pgm_negative(&negative, &my_pgm);
    pgm_symmetry_hori(&sym_h, &my_pgm);
    pgm_symmetry_vert(&sym_v, &my_pgm);
    pgm_symmetry_cent(&sym_c, &my_pgm);
    pgm_photomaton(&photo, &my_pgm);
    pgm_crop(&crop, &my_pgm, 100, 200, 100, 200);
    pgm_conv(&conv, &my_pgm, &kernel);

    //save pgm to files
    pgm_write_to_file(&my_pgm, "out.pgm");
    pgm_write_to_file(&negative, "out_negative.pgm");
    pgm_write_to_file(&sym_h, "out_sym_h.pgm");
    pgm_write_to_file(&sym_v, "out_sym_v.pgm");
    pgm_write_to_file(&sym_c, "out_sym_c.pgm");
    pgm_write_to_file(&photo, "out_photomaton.pgm");
    pgm_write_to_file(&crop,"out_crop.pgm");
    pgm_write_to_file(&conv,"out_conv.pgm");


    //show pgm with SDL2
    struct gfx_context_t *ctxt = gfx_create("Example", my_pgm.pixels.m, my_pgm.pixels.n);
	if (!ctxt) {
		fprintf(stderr, "Graphics initialization failed!\n");
		return EXIT_FAILURE;
	}

	while (gfx_keypressed() != SDLK_ESCAPE) {
		render(ctxt, negative);
		gfx_present(ctxt);
	}

    //destroy elements 
	gfx_destroy(ctxt);
    matrix_destroy(&my_pgm.pixels);
    matrix_destroy(&negative.pixels);
    matrix_destroy(&sym_h.pixels);
    matrix_destroy(&sym_v.pixels);
    matrix_destroy(&sym_c.pixels);
    matrix_destroy(&photo.pixels);
    matrix_destroy(&crop.pixels);
    matrix_destroy(&conv.pixels);
    matrix_destroy(&kernel);    
}