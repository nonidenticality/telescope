#include <stdlib.h>
#include <math.h>

#include "stars.h"

static View view;

void setup_stars() {
    view.seed = rand();
}

void render_star(WINDOW *win, View* view, int x, int y) {
    int seed = view->seed;

    if (!((seed + (int)(191 * cos(x & y) + 13 * (x | y) - 31 * x * y * cos(x ^ y))) % 13)) {
        if (!((int)(seed + (x + y * cos(x | y) + cos(x ^ y))) % 3)) {
            mvwprintw(win, y, x, "*");
        } else {
            mvwprintw(win, y, x, ".");
        }
    }
}

void render_stars(WINDOW *win) {
    for (int i = 1; i < LINES - 1; i++) {
        for (int j = 1; j < COLS - 1; j++) {
            render_star(win, &view, j, i);
        }
    }
}

void wipe_stars() {
    view.seed = rand();
}

void finish_stars() { }
