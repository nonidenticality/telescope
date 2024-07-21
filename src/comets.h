#ifndef COMETS_H
#define COMETS_H

#include <ncurses.h>

typedef enum {
    LEFT,
    RIGHT
} HDirection;

typedef enum {
    UP,
    DOWN,
} VDirection;

typedef struct {
    unsigned int lifespan, halflife, size, trail;
    unsigned int startX, startY, currentX, currentY;
} Comet;

typedef struct {
    Comet **comets;
    unsigned int size;
    HDirection xDir;
    VDirection yDir;
} CometStorm;

void comets_setup();

void spawn_new_comets();

void wipe_comets();

void move_comets();

void render_comets(WINDOW *win);

void comets_finish();

#endif
