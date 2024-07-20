#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

#include "stars.h"

static WINDOW * win = NULL;
static WINDOW * timer_win = NULL;

static int STARTING_Y = 0;
static int STARTING_X = 0;
static int WIDTH;
static int HEIGHT;

void setup() {
    initscr();

    WIDTH = COLS;
    HEIGHT = LINES;

    win = newwin(HEIGHT, WIDTH, STARTING_X, STARTING_Y);
    timer_win= newwin(3, 10, 1, 1);

    noecho();
    wtimeout(win, 0);
    curs_set(0);
}

void render_star(View* view, int x, int y) {
    int seed = view->seed;

    if (!((seed + (int)(191 * cos(x & y) + 13 * (x | y) - 31 * x * y * cos(x ^ y))) % 13)) {
        if (!((int)(seed + (x + y * cos(x | y) + cos(x ^ y))) % 3)) {
            mvwprintw(win, y, x, "*");
        } else {
            mvwprintw(win, y, x, ".");
        }
    }
}

void render_stars(View *view) {
    for (int i = STARTING_Y + 1; i < LINES - 1; i++) {
        for (int j = STARTING_X + 1; j < COLS - 1; j++) {
            render_star(view, j, i);
        }
    }
}

char* get_current_time() {
    time_t t;
    time(&t);
    struct tm *t_info = localtime(&t);

    char* text = malloc(sizeof(char) * 9);
    sprintf(text, "%02d:%02d:%02d",
            t_info->tm_hour,
            t_info->tm_min,
            t_info->tm_sec);
    return text;
}

void render_timer() {
    werase(timer_win);
    char* time = get_current_time();
    for (int i = 0; i < 9; i++) {
        if (!time[i]) break;
        mvwaddch(timer_win, 1, i + 1, time[i]);
    }
    free(time);
    box(timer_win, 0, 0);
    wrefresh(timer_win);
}

void render(View *view) {
    wipe();
    render_stars(view);
    box(win, 0, 0);
    wresize(win, LINES, COLS);
    wrefresh(win);
    render_timer();
}

void wipe() {
    werase(win);
}

int take_input() {
    return wgetch(win);
}

void finish() {
    clear();

    delwin(win);
    win = NULL;

    delwin(timer_win);
    timer_win = NULL;

    endwin();
}
