#ifndef STARS_H
#define STARS_H

typedef struct {
    long seed;
    unsigned int x, y;
} View;

void setup(void);

void render(View*);

void wipe(void);

int take_input(void);

void finish(void);

#endif
