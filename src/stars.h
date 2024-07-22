#ifndef STARS_H
#define STARS_H

#include <ncurses.h>

typedef struct {
    long seed;
} View;

void setup_stars(void);

void render_stars(WINDOW*);

void wipe_stars(void);

void finish_stars(void);

#endif
