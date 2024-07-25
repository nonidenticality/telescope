#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "timer.h"

WINDOW * timer_win;

static unsigned int TIMER_WIDTH = 10,
                    TIMER_HEIGHT = 3;

void setup_timer() {
    timer_win = newwin(TIMER_HEIGHT, TIMER_WIDTH, 1, 1);
}

char* get_time() {
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

void wipe_timer() {
    werase(timer_win);
}

void render_timer() {
    werase(timer_win);
    char* time = get_time();
    for (int i = 0; i < 9; i++) {
        if (!time[i])
            break;
        mvwaddch(timer_win, 1, i + 1, time[i]);
    }
    free(time);
    box(timer_win, 0, 0);
    wrefresh(timer_win);
}

void finish_timer() {
    delwin(timer_win);
    timer_win = NULL;
}
