#ifndef F_GAME_H
#define F_GAME_H

#include "f_grid.h"
#include "sg_queue.h"

#define MIN_GRID_SIZE 5
#define MAX_GRID_SIZE 20

int play_game(struct grid *sg, struct grid *ug, struct grid *ig, int shots, struct sg_queue *posx_visited, struct sg_queue *posy_visited);
int valid_input(const struct grid *gd, char chars_pos[], int nums_pos[]);
int is_hit(struct grid *sg, struct grid *ug, struct grid *ig, const int posx, const int posy, int *sh_sunken);
void update_damage(struct grid *sg, struct grid *ig, const int posx, const int posy, int *sh_sunken);
int repeated(const int nums_pos[], struct sg_queue *posx_visited, struct sg_queue *posy_visited);
void organize_input(char chars_pos[]);

#endif