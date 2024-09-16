#ifndef F_GAME_H
#define F_GAME_H

#include "f_grid.h"

int play_game(struct grid *sg, struct grid *ug, int shells);
int valid_input(char c1, char c2);

#endif