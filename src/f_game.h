#ifndef F_GAME_H
#define F_GAME_H

#include "f_grid.h"

#define MIN_GRID_SIZE 5
#define MAX_GRID_SIZE 20

int play_game(struct grid *sg, struct grid *ug, int shells);
int valid_input(struct grid *gd, char c1, char c2);

#endif