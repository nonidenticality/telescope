#include <stdlib.h>
#include <ncurses.h>

#include "renderer.h"

#include "defs.h"
#include "stars.h"
#include "comets.h"
#include "aliens.h"
#include "timer.h"

static WINDOW * win = NULL;

void resize() {
    if (win != NULL) {
        wresize(win, getHeight(), getWidth());
    }
}

void setup() {
    initscr();

    win = newwin(getHeight(), getWidth(), 0, 0);

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
    render_aliens(win);

    move_comets();
    spawn_new_comets();

    move_aliens();
    spawn_new_aliens();

    wrefresh(win);
}

int take_input() {
    return wgetch(win);
}

void wipe() {
    wipe_stars();
    wipe_comets();
    wipe_aliens();
    wipe_timer();
}

void finish() {
    delwin(win);
    win = NULL;

    finish_stars();
    finish_comets();
    finish_aliens();
    finish_timer();

    endwin();
}
