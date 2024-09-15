#ifndef F_GRID_H
#define F_GRID_H

#include "f_ship.h"

#define CARRIERS 1
#define BATTLESHIPS 1
#define FRIGATES 2
#define TOTAL_SHIPS (CARRIERS + BATTLESHIPS + FRIGATES)

#define WATER '-'

struct grid {
    int size;
    char **elements;
    struct ship *ships[TOTAL_SHIPS];
};

struct grid *new_grid(int grid_size);
void water_grid(struct grid *gd);
void ships_grid(struct grid *gd);
int place_available(struct grid *gd, struct ship *sp, int posx, int posy, int horizontal);
void place_ship(struct grid *gd, struct ship *nf, int posx, int posy);
int valid_position(const struct grid *gd, int posx, int posy);
void set_value_at(struct grid *gd, int pos_x, int pos_y, char value);
void print_grid(const struct grid *gd);
void delete_grid(struct grid *gd);

#endif