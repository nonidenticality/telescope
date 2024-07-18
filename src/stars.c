#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

#include "stars.h"

static WINDOW * win = NULL;

static int STARTING_Y = 0;
static int STARTING_X = 0;
static int WIDTH;
static int HEIGHT;

void setup() {
    initscr();

    WIDTH = COLS;
    HEIGHT = LINES;

    cbreak();
    noecho();
    curs_set(0);

    win = newwin(HEIGHT, WIDTH, STARTING_X, STARTING_Y);
}

long get_current_time() {
    time_t timer;
    return time(&timer);
}

void animate_star(int x, int y) {
    char time_factor = (int)(get_current_time());

    if (time_factor % 2) {
        mvwprintw(win, y, x, "*");
    } else {
        mvwprintw(win, y, x, "·");
    }
}

void render_star(View* view, int x, int y) {
    int seed = view->seed;
    
    if (!((seed + (int)(191 * cos(x & y) + 13 * (x | y) - 31 * x * y * cos(x ^ y))) % 13)) {
        if (!((int)(seed + (x + y * cos(x | y) + cos(x ^ y))) % 3)) {
            mvwprintw(win, y, x, "*");
        } else {
            mvwprintw(win, y, x, "·");
            // animate_star(x, y);
        }
    }
}

void render_stars(View *view) {
    for (int i = STARTING_Y + 1; i < HEIGHT - 1; i++) {
        for (int j = STARTING_X + 1; j < WIDTH - 1; j++) {
            render_star(view, j, i);
        }
    }
}

void render(View *view) {
    box(win, 0, 0);
    render_stars(view);
    wrefresh(win);
}

void wipe() {
    wclear(win);
}

int take_input() {
    return wgetch(win);
}

void finish() {
    delwin(win);
    win = NULL;
    endwin();
}
