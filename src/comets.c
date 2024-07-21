#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "comets.h"

static const unsigned int COMET_LIMIT = 2;

static CometStorm storm;

char get_direction_char() {
    if (storm.xDir == RIGHT) {
        if (storm.yDir == UP) {
            return '/';
        } else {
            return '\\';
        }
    } else {
        if (storm.yDir == UP) {
            return '\\';
        } else {
            return '/';
        }
    }
    return ' ';
}

int get_trail_x(Comet *comet, unsigned int i) {
    if (storm.xDir == LEFT) {
        return comet->currentX - i;
    }
    return comet->currentX + i;
}

int get_trail_y(Comet *comet, unsigned int i) {
    if (storm.yDir == UP) {
        return comet->currentY - i;
    }
    return comet->currentY + i;
}

void render_trail(WINDOW *win, Comet *comet) {
    for (unsigned int i = 0; i < comet->trail; i++) {
        mvwaddch(win,
                 get_trail_y(comet, i),
                 get_trail_x(comet, i),
                 get_direction_char());
    }
}

void render_head(WINDOW *win, Comet *comet) {
    mvwaddch(win, comet->currentY, comet->currentX,
             get_direction_char());
}


static void set_direction(int r) {
    switch (r) {
        case 0:
            storm.xDir = RIGHT;
            storm.yDir = UP;
            break;
        case 1:
            storm.xDir = LEFT;
            storm.yDir = UP;
            break;
        case 2:
            storm.xDir = RIGHT;
            storm.yDir = DOWN;
            break;
        default:
        case 3:
            storm.xDir = RIGHT;
            storm.yDir = UP;
            break;
    }
}

void refresh_storm() {
    set_direction(rand() % 4);
}

static Comet *add_comet(unsigned int width, unsigned int height) {
    Comet *comet = malloc(sizeof(Comet));
    comet->startX = comet->currentX = rand() % width;
    comet->startY = comet->currentY = rand() % height;
    comet->halflife = 10;
    comet->lifespan = 0;

    comet->trail = 0;
    return comet;
}


static void move_comet(Comet *comet) {
    if (storm.yDir == UP) {
        comet->currentY--;
    } else if (storm.yDir == DOWN) {
        comet->currentY++;
    }

    if (storm.xDir == RIGHT) {
        comet->currentX++;
    } else if (storm.xDir == LEFT) {
        comet->currentX--;
    }

    if (comet->lifespan < comet->halflife) {
        comet->lifespan++;
        comet->trail++;
    } else if (comet->trail > 0) {
        comet->trail--;
    }
}

void move_comets() {
    for (unsigned int i = 0; i < storm.size; i++) {
        move_comet(storm.comets[i]);
    }
}

void delete_comet(Comet *comet) {
    free(comet);
}

void clear_comets() {
    for (unsigned int i = 0; i < storm.size; i++) {
        delete_comet(storm.comets[i]);
        storm.comets[i] = NULL;
    }
    storm.size = 0;
}

void comets_setup() {
    storm.size = 0;
    storm.comets = malloc(sizeof(Comet*) * COMET_LIMIT);
}

void wipe_comets() {
    clear_comets();
    refresh_storm();
}

long current_time() {
    return time(NULL);
}

bool is_below_size_limit() {
    return storm.size <= COMET_LIMIT;
}

bool is_comet_expired(Comet *comet) {
    return comet->lifespan >= comet->halflife;
}

bool is_every_comet_expired() {
    for (unsigned int i = 0; i < storm.size; i++) {
        Comet *comet = storm.comets[i];
        if (!is_comet_expired(comet)) {
            return false;
        }
    }
    return true;
}

void spawn_new_comets() {
    if (is_every_comet_expired()) {
        clear_comets();
    }
    if (!is_below_size_limit()) {
        return;
    }
    Comet *new_comet = add_comet(COLS, LINES);
    storm.comets[storm.size] = new_comet;
    storm.size++;
}

void render_comet(WINDOW *win, Comet *comet) {
    if (comet->lifespan <= comet->halflife) {
        render_trail(win, comet);
        render_head(win, comet);
    } else {
        delete_comet(comet);
    }
    wrefresh(win);
}

void render_comets(WINDOW *win) {
    for (unsigned int i = 0; i < storm.size; i++) {
        render_comet(win, storm.comets[i]);
    }
}

void comets_finish() {
    clear_comets();
    free(storm.comets);
}
