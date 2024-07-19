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

    win = newwin(HEIGHT, WIDTH, STARTING_X, STARTING_Y);

    noecho();
    wtimeout(win, 0);
    curs_set(0);

    WIDTH = COLS;
    HEIGHT = LINES;


}

void render_star(View* view, int x, int y) {
    int seed = view->seed;
    
    if (!((seed + (int)(191 * cos(x & y) + 13 * (x | y) - 31 * x * y * cos(x ^ y))) % 13)) {
        if (!((int)(seed + (x + y * cos(x | y) + cos(x ^ y))) % 3)) {
            mvwprintw(win, y, x, "*");
        } else {
            mvwprintw(win, y, x, "·");
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

char* get_current_time() {
    time_t t;
    time(&t);
    struct tm *t_info = localtime(&t);

    char* array = malloc(sizeof(char) * 9);
    sprintf(array, "%02d:%02d:%02d", t_info->tm_hour, t_info->tm_min, t_info->tm_sec);
    return array;
}

void render_timer() {
    WINDOW *timer_win = newwin(3, 10, 1, 1);
    box(timer_win, 0, 0);
    char* time = get_current_time();
    for (int i = 0; i < 9; i++) {
        if (!time[i]) break;
        mvwaddch(timer_win, 1, i  + 1, time[i]);
    }
    free(time);
    wrefresh(timer_win);
    delwin(timer_win);
}

void render(View *view) {
    box(win, 0, 0);
    render_stars(view);
    wrefresh(win);
    render_timer();
}

void wipe() {
    wclear(win);
}

int take_input() {
    return wgetch(win);
}

void finish() {
    clear();
    delwin(win);
    win = NULL;
    endwin();
}
