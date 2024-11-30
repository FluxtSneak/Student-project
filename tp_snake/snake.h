#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <bits/stdint-intn.h>
#include <stdbool.h>
#include "queue_list.h"
#include "gfx.h"

typedef enum _direction {
UP,
DOWN, 
RIGHT, 
LEFT
}direction;
typedef enum _map {
wall=COLOR_BLUE,
food=COLOR_RED, 
body=COLOR_GREEN, 
empty=COLOR_BLACK
}map;

typedef struct _snake {
queue_lst pos;
int direction;
bool isAlive;
int foodAct;
} snake;


void initGame(snake *snk, struct gfx_context_t *ctxt,int width, int height);
void initSnake(snake *snk, int width, int height);
void move(snake *snk, struct gfx_context_t *ctxt);
void createFood(struct gfx_context_t *ctxt, snake *snk, int width, int height);
void changedirection(snake *snk, SDL_Keycode key);

#endif


