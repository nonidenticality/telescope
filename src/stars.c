#include <ncurses.h>

#include "stars.h"

static WINDOW * win = NULL;

static int STARTING_Y = 0;
static int STARTING_X = 0;
static int WIDTH;
static int HEIGHT;

void setup() {
    initscr();

    WIDTH = COLS - 1;
    HEIGHT = LINES - 1;

    raw();
    cbreak();
    noecho();

    win = newwin(HEIGHT, WIDTH, STARTING_X, STARTING_Y);
}

void render_star(int x, int y) {
    if (!(((x * y) - (x ^ y)) % 17)) {
        mvwprintw(win, y, x, "*");
    }
}

void render_stars() {
    for (int i = STARTING_Y + 1; i < HEIGHT - 1; i++) {
        for (int j = STARTING_X + 1; j < WIDTH - 1; j++) {
            render_star(j, i);
        }
    }
}

void render(View *view) {
    box(win, 0, 0);
    render_stars();
    wrefresh(win);
}

int take_input() {
    return getch();
}

void finish() {
    delwin(win);
    win = NULL;
    endwin();
}
