#ifndef ALIENS_H
#define ALIENS_H

#include <ncurses.h>

void setup_aliens(void);

void render_aliens(WINDOW*);

void spawn_new_aliens(void);

void move_aliens(void);

void wipe_aliens(void);

void finish_aliens(void);

#endif
