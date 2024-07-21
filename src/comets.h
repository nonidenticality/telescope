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
    unsigned long seed;
    unsigned int lifespan, halflife, size, trail;
    unsigned int startX, startY, currentX, currentY;
    HDirection xDir;
    VDirection yDir;
} Comet;


Comet * create_comet(unsigned int, unsigned int);

void move_comet(Comet *comet);

void render_comet(WINDOW *win, Comet *comet);

void delete_comet(Comet *comet);

#endif
