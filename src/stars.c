#include <ncurses.h>

#include "stars.h"

WINDOW * win = NULL;

void setup() {
    initscr();

    raw();
    cbreak();
    noecho();

    win = newwin(LINES - 1, COLS - 1, 1, 1);
}

void render(View *view) {
    box(win, 0, 0);
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
