#include <stdlib.h>

#include "comets.h"

char get_direction_char(Comet *comet) {
    if (comet->xDir == RIGHT) {
        if (comet->yDir == UP) {
            return '/';
        } else {
            return '\\';
        }
    } else {
        if (comet->yDir == UP) {
            return '\\';
        } else {
            return '/';
        }
    }
    return ' ';
}

int get_trail_x(Comet *comet, unsigned int i) {
    if (comet->xDir == LEFT) {
        return comet->currentX - i;
    }
    return comet->currentX + i;
}

int get_trail_y(Comet *comet, unsigned int i) {
    if (comet->yDir == UP) {
        return comet->currentY - i;
    }
    return comet->currentY + i;
}

void render_trail(WINDOW *win, Comet *comet) {
    for (unsigned int i = 0; i < comet->trail; i++) {
        mvwaddch(win,
                 get_trail_y(comet, i),
                 get_trail_x(comet, i),
                 get_direction_char(comet));
    }
}

void render_head(WINDOW *win, Comet *comet) {
    mvwaddch(win, comet->currentY, comet->currentX,
             get_direction_char(comet));
}

void render_comet(WINDOW *win, Comet *comet) {
    if (comet->halflife <= comet->lifespan) {
        render_trail(win, comet);
        render_head(win, comet);
    }
    wrefresh(win);
}

void set_direction(Comet *comet, int r) {
    switch (r) {
        case 0:
            comet->xDir = RIGHT;
            comet->yDir = UP;
            break;
        case 1:
            comet->xDir = LEFT;
            comet->yDir = UP;
            break;
        case 2:
            comet->xDir = RIGHT;
            comet->yDir = DOWN;
            break;
        default:
        case 3:
            comet->xDir = RIGHT;
            comet->yDir = UP;
            break;
    }
}

Comet *create_comet(unsigned int width, unsigned int height) {
    Comet *comet = malloc(sizeof(Comet));
    comet->seed = rand();
    comet->startX = comet->currentX = rand() % width;
    comet->startY = comet->currentY = rand() % height;
    comet->halflife = 10;
    comet->lifespan = 0;
    comet->xDir = rand() % 2;
    comet->yDir = rand() % 2;

    comet->trail = rand() % 7;
    return comet;
}

void move_comet(Comet *comet) {
    if (comet->yDir == UP) {
        comet->currentY--;
    } else if (comet->yDir == DOWN) {
        comet->currentY++;
    }

    if (comet->xDir == RIGHT) {
        comet->currentX++;
    } else if (comet->xDir == LEFT) {
        comet->currentX--;
    }

    if (comet->lifespan < comet->halflife) {
        comet->lifespan++;
        comet->trail++;
    } else if (comet->trail > 0) {
        comet->trail--;
    }
}

void delete_comet(Comet *comet) {
    free(comet);
}
