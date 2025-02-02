#include <stdlib.h>
#include <math.h>

#include "stars.h"
#include "defs.h"

static View view;

void setup_stars() {
    view.seed = rand();
}

char is_renderable(int seed, int x, int y) {
    return !((seed + (int)(191 * cos(x & y) + 13 * (x | y) - 31 * x * y * cos(x ^ y))) % 13);
}

char is_large(int seed, int x, int y) {
    return !((int)(seed + (x + y * cos(x | y) + cos(x ^ y))) % 3);
}

void render_star(WINDOW *win, View* view, int x, int y) {
    int seed = view->seed;

    if (is_renderable(seed, x, y)) {
        if (is_large(seed, x, y)) {
            mvwprintw(win, y, x, "*");
        } else {
            mvwprintw(win, y, x, ".");
        }
    }
}

void render_stars(WINDOW *win) {
    for (unsigned int i = 1; i < getHeight() - 1; i++) {
        for (unsigned int j = 1; j < getWidth() - 1; j++) {
            render_star(win, &view, j, i);
        }
    }
}

void wipe_stars() {
    view.seed = rand();
}

void finish_stars() { }
