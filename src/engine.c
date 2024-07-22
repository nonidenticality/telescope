#include <stdlib.h>
#include <ncurses.h>

#include "stars.h"
#include "comets.h"
#include "timer.h"

static WINDOW * win = NULL;
static unsigned int WIDTH, HEIGHT;

void resize() {
    WIDTH = COLS;
    HEIGHT = LINES;
    wresize(win, HEIGHT, WIDTH);
}

void setup() {
    initscr();

    win = newwin(LINES, COLS, 0, 0);

    noecho();
    wtimeout(win, 0);
    curs_set(0);
    resize();

    setup_stars();
    setup_comets();
    setup_timer();
}

void render() {
    resize();
    werase(win);

    render_stars(win);
    render_comets(win);

    move_comets();
    spawn_new_comets();

    box(win, 0, 0);
    wrefresh(win);

    render_timer();
}

int take_input() {
    return wgetch(win);
}

void wipe() {
    wipe_stars();
    wipe_comets();
    wipe_timer();
}

void finish() {
    delwin(win);
    win = NULL;

    finish_stars();
    finish_comets();
    finish_timer();

    endwin();
}
