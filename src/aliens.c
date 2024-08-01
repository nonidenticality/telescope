#include <stdlib.h>
#include "aliens.h"
#include "clock.h"

enum AlienState{
    INACTIVE,
    ACTIVE,
    VROOMING,
};

static const enum AlienState INITIAL_STATE = INACTIVE;
static const char *SHIP_CHAR = "0";

typedef struct {
    enum AlienState state;
    unsigned int x, y,
                vX, vY,
                toX, toY;
} Alien;

static Alien aliens[3] = {
    { INITIAL_STATE, 0, 0, 0, 0, 15, 15},
    { INITIAL_STATE, 0, 0, 0, 0, 5, 5},
    { INITIAL_STATE, 0, 0, 0, 0, 10, 10},
};

unsigned int aliens_length = sizeof(aliens) / sizeof(Alien);

void setup_aliens() {
    
}

void render_alien(WINDOW *win, Alien *alien) {
    //mvwprintw(win, alien->y, alien->x, "%s", SHIP_CHAR);
    mvwprintw(win, alien->y, alien->x, "%s", SHIP_CHAR);
}

void render_vroom(WINDOW *win, Alien *alien) {
    mvwprintw(win, alien->y, alien->x, "o");
}

void render_aliens(WINDOW* win) {
    for (unsigned int i = 0; i < aliens_length; i++) {
        Alien alien = aliens[i];
        if (alien.state == ACTIVE) {
            render_alien(win, &alien);
        } else if (alien.state == VROOMING) {
            render_vroom(win, &alien);
        }
    }
}

void set_random_position(Alien* alien) {
    alien->x = rand() % COLS;
    alien->y = rand() % LINES;
}

void cycle_aliens() {
    unsigned long current_nanoseconds = get_current_nanoseconds();
    for (unsigned int i = 0; i < aliens_length; i++) {
        if (!((i + 1 + current_nanoseconds) % aliens_length)) {
            continue;
        }
        if (!(current_nanoseconds % 171)) {
            if (aliens[i].state == ACTIVE) {
                aliens[i].state = INACTIVE;
                break;
            }
        }
        if (!(current_nanoseconds % 531)) {
            if (aliens[i].state == INACTIVE) {
                aliens[i].state = ACTIVE;
                set_random_position(&aliens[i]);
                break;
            }
        }
    }
}

void spawn_new_aliens() {
    cycle_aliens();
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
    } else {
        alien->vX = 0;
    }

    if (alien->y < alien->toY) {
        // alien->vY = (rand() % 2);
        alien->vY = 1;
    } else if (alien->y > alien->toY) {
        // alien->vY = (rand() % 2) - 2;
        alien->vY = -1;
    } else {
        alien->vY = 0;
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
    for (unsigned int i = 0; i < aliens_length; i++) {
        set_random_position(&aliens[i]);
        aliens[i].state = INACTIVE;
    }
}

void finish_aliens() {
    
}
