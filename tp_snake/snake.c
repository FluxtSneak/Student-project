#include "snake.h"
#include "gfx.h"
#include "queue_list.h"
#include "time.h"
#include "unistd.h"
#include <SDL2/SDL_keycode.h>

void initGame(snake *snk, struct gfx_context_t *ctxt, int width, int height){
    snk->direction=RIGHT;
    initSnake(snk,width, height);
    for(int i =0;i<height;i++){
        for(int j=0;j<width;j++){
            if(i==0 ||j==0||i==height-1||j==width-1)gfx_putpixel(ctxt,j,i,wall);
        }
    }
}
void initSnake(snake *snk, int width, int height){
    snk->isAlive=true;
    snk->foodAct=0;
    pixel px;
    px.col=width/2;
    px.line=height/2;
    snk->pos=queue_create_lst();
    for (int i=0;i<3;i++){
        queue_insert_lst(&snk->pos,px);        
        px.col--;        
    }
}
void move(snake *snk, struct gfx_context_t *ctxt){
    pixel px = queue_head_lst(snk->pos);
    
    switch(snk->direction){
        case UP:
            px.line--;            
        break;
        case DOWN:
            px.line++;
        break;
        case RIGHT:
            px.col++;
        break;
        case LEFT:
            px.col--;
        break;
    }
    uint32_t next=gfx_getpixel(ctxt, px.col, px.line);
    queue_insert_lst(&snk->pos,px);
    gfx_putpixel(ctxt, px.col, px.line, body);
    if(next==empty){
        pixel p=queue_extract_lst(&snk->pos);
        gfx_putpixel(ctxt, p.col, p.line, empty);

    }
    else if(next==wall){
        snk->isAlive=false;
        printf("Boom le mur\n\n\n");
    }
    else if(next==body){
        printf("Boom le body\n\n\n");
        snk->isAlive=false;
    }
    else if(next==food)snk->foodAct--;
}
void changedirection(snake *snk, SDL_Keycode key){
    switch(key){
    case SDLK_RIGHT:
      snk->direction=RIGHT;
    break;
    case SDLK_LEFT:
    snk->direction=LEFT; 
    break;
    case SDLK_UP:
    snk->direction=UP;
    break;
    case SDLK_DOWN:
    snk->direction=DOWN;
    break;
  }
}
void createFood(struct gfx_context_t *ctxt, snake *snk,int width, int height){
    srand (time(NULL));
    int x=rand()%(width-1);
    int y=rand()%(height-1);
    while(gfx_getpixel(ctxt,x,y)!=empty){
        x=rand()%(width-1);
        y=rand()%(height-1);
    }
    gfx_putpixel(ctxt, x, y, food);
    snk->foodAct++;
}