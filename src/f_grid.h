#ifndef F_GRID_H
#define F_GRID_H

#include "f_ship.h"

#define CARRIERS 1
#define BATTLESHIPS 1
#define FRIGATES 2
#define TOTAL_SHIPS (CARRIERS + BATTLESHIPS + FRIGATES)

#define WATER '~'
#define HIT 'h'
#define MISS 'm'

#define HIT_COLOR "\033[1;91m"
#define MISS_COLOR "\033[1;92m"
#define CARRIER_COLOR "\033[1;93m"
#define BATTLESHIP_COLOR "\033[1;94m"
#define FRIGATE_COLOR "\033[1;95m"
#define WATER_COLOR "\033[1;96m"
#define RESET_COLOR "\033[0m"

struct grid {
    int size;
    char **elements;
    struct ship *ships[TOTAL_SHIPS];
};

struct grid *new_grid(const int grid_size);
void water_grid(struct grid *gd);
void ships_grid(struct grid *gd);
int place_available(const struct grid *gd, const struct ship *sp, const int posx, const int posy, const int orientation);
void place_ship(struct grid *gd, const struct ship *sp, int posx, int posy);
int valid_position(const struct grid *gd, const int posx, const int posy);
void print_grid(const struct grid *gd);
void delete_grid(struct grid *gd);

#endif