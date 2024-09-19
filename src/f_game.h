#ifndef F_GAME_H
#define F_GAME_H

#include "f_grid.h"

#define MIN_GRID_SIZE 5
#define MAX_GRID_SIZE 20

#define HIT 'h'
#define MISS 'm'

int play_game(struct grid *sg, struct grid *ug, int shots);
int valid_input(struct grid *gd, char chars_pos[], int nums_pos[]);
int is_hit(struct grid *sg, struct grid *ug, int posx, int posy);
void swap_chars(char chars_pos[]);

#endif