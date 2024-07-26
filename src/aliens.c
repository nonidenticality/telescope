#include <stdlib.h>

#include "aliens.h"
#include "clock.h"


static const char *SHIP_CHAR = "(O)";

typedef struct {
    unsigned int x, y,
                vX, vY,
                toX, toY;
} Alien;

Alien aliens[3] = {
    { 0, 0, 0, 0, 15, 15},
    { 0, 0, 0, 0, 5, 5},
    { 0, 0, 0, 0, 10, 10},
};

unsigned int aliens_length = sizeof(aliens) / sizeof(Alien);

void setup_aliens() {
    
}

void render_alien(WINDOW *win, Alien *alien) {
    //mvwprintw(win, alien->y, alien->x, "%s", SHIP_CHAR);
    mvwprintw(win, alien->y, alien->x, "%s", SHIP_CHAR);
}

void render_aliens(WINDOW* win) {
    for (unsigned int i = 0; i < aliens_length; i++) {
        Alien alien = aliens[i];
        render_alien(win, &alien);
    }
}

void spawn_new_aliens() {
    
}

void new_interest_point(Alien *alien) {
    alien->toX = rand() % COLS;
    alien->toY = rand() % LINES;
}

void move_alien(Alien *alien) {
    if (!(get_current_nanoseconds() % 15)) {
        new_interest_point(alien);
    }

    if (get_current_nanoseconds() % 2) {
        return;
    }

    if (alien->x < alien->toX) {
        // alien->vX = (rand() % 2);
        alien->vX = 1;
    } else if (alien->x > alien->toX) {
        // alien->vX = (rand() % 2) - 2;
        alien->vX = -1;
    }

    if (alien->y < alien->toY) {
        // alien->vY = (rand() % 2);
        alien->vY = 1;
    } else if (alien->y > alien->toY) {
        // alien->vY = (rand() % 2) - 2;
        alien->vY = -1;
    }

    alien->x += alien->vX;
    alien->y += alien->vY;
}

void move_aliens() {
    for (unsigned int i = 0; i < aliens_length; i++) {
        move_alien(&aliens[i]);
    }
}

void wipe_aliens() {
    
}

void finish_aliens() {
    
}
