#ifndef STARS_H
#define STARS_H

typedef struct {
    long seed;
    unsigned int x, y;
} View;

void setup(void);

void render(View*);

int take_input(void);

void finish(void);

#endif
