#include <stdlib.h>
#include "aliens.h"
#include "math.h"
#include "defs.h"
#include "clock.h"

enum AlienState{
    INACTIVE,
    ACTIVE,
    VROOMING_OUT,
    VROOMING_IN
};

static const enum AlienState INITIAL_STATE = INACTIVE;
static const char *SHIP_CHAR = "0";

typedef struct {
    enum AlienState state;
    unsigned int stateLength,
                x, y,
                vX, vY,
                toX, toY;
} Alien;

static Alien aliens[3] = {
    { INITIAL_STATE, 0, 0, 0, 0, 0, 15, 15},
    { INITIAL_STATE, 0, 0, 0, 0, 0, 5, 5},
    { INITIAL_STATE, 0, 0, 0, 0, 0, 10, 10},
};

unsigned int aliens_length = sizeof(aliens) / sizeof(Alien);

void setup_aliens() {
    
}

void render_alien(WINDOW *win, Alien *alien) {
    //mvwprintw(win, alien->y, alien->x, "%s", SHIP_CHAR);
    mvwprintw(win, alien->y, alien->x, "%s", SHIP_CHAR);
}

void render_vroom(WINDOW *win, Alien *alien) {
    if (get_current_time() % 2) {
        mvwprintw(win, alien->y, alien->x, "x");
    } else {
        mvwprintw(win, alien->y, alien->x, "+");
    }
}

void render_aliens(WINDOW* win) {
    for (unsigned int i = 0; i < aliens_length; i++) {
        Alien alien = aliens[i];
        switch (alien.state) {
            case ACTIVE:
                render_alien(win, &alien);
                break;
            case VROOMING_IN:
            case VROOMING_OUT:
                render_vroom(win, &alien);
                break;
            default:
                break;
                
        }
    }
}

void set_random_position(Alien* alien) {
    alien->x = rand() % getWidth();
    alien->y = rand() % getHeight();
}

void cycle_active_alien(Alien *alien) {
    if (!(get_current_time() % 171)) {
        alien->state = VROOMING_OUT;
        alien->stateLength = 0;
    }
}

void cycle_vrooming_in_alien(Alien * alien) {
    if (alien->stateLength >= 50) {
        alien->state = ACTIVE;
    }
}

void cycle_vrooming_out_alien(Alien * alien) {
    if (alien->stateLength >= 50) {
        alien->state = INACTIVE;
    }
}

void cycle_inactive_alien(Alien *alien) {
    if (!(get_current_time() % 531)) {
        alien->state = VROOMING_IN;
        set_random_position(alien);
        alien->stateLength = 0;
    }
}

void cycle_alien_state(Alien *alien) {
    switch (aliens->state) {
        case ACTIVE:
            cycle_active_alien(alien);
            break;
        case VROOMING_IN:
            cycle_vrooming_in_alien(alien);
            break;
        case VROOMING_OUT:
            cycle_vrooming_out_alien(alien);
            break;
        case INACTIVE:
            cycle_inactive_alien(alien);
            break;
    }
}

void cycle_aliens() {
    for (unsigned int i = 0; i < aliens_length; i++) {
        aliens[i].stateLength++;
        if (!((i + 1 + get_current_time()) % aliens_length)) {
            continue;
        }
        cycle_alien_state(&aliens[i]);
    }
}

void spawn_new_aliens() {
    cycle_aliens();
}

void new_interest_point(Alien *alien) {
    alien->toX = rand() % getWidth();
    alien->toY = rand() % getHeight();
}

int vary_velocity(int var1, int var2) {
    return sin((float)((var1 ^ var2) % 10) / 4 * M_PI);
}

void move_alien(Alien *alien) {
    if (!(get_current_time() % 71)) {
        new_interest_point(alien);
    }

    if (get_current_time() % 2) {
        return;
    }

    if (alien->state == VROOMING_IN
        || alien->state == VROOMING_OUT) {
        return;
    }

    unsigned int x = alien->x,
                 y = alien->y,
                 toX = alien->toX,
                 toY = alien->toY;

    if (x < toX) {
        alien->vX = vary_velocity(x, y) + 1;
    } else if (x > toX) {
        alien->vX = vary_velocity(x, y) - 1;
    } else {
        // alien->vX = 0;
    }

    if (y < toY) {
        alien->vY = vary_velocity(x, y) + 1;
    } else if (y > toY) {
        alien->vY = vary_velocity(x, y) - 1;
    } else {
        // alien->vY = 0;
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
