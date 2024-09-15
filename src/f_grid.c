#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "f_grid.h"

struct grid *new_grid(int grid_size) {
    struct grid *ng = (struct grid *)malloc(sizeof(struct grid));
    
    if (ng == NULL) {
        perror("Cannot allocate memory for new grid object.");
        
        exit(EXIT_FAILURE);
    }
    
    /* Allocate a 1 x grid_size array to hold pointers to more arrays */
    ng->elements = (char **)malloc(sizeof(char *) * grid_size);
    
    if (ng->elements == NULL) {
        perror("Cannot allocate memory for new grid.");
        
        exit(EXIT_FAILURE);
    }
    
    /* Allocate each row in that column */
    for (int i = 0; i < grid_size; i++) {
        ng->elements[i] = (char *)malloc(sizeof(char) * grid_size);
        
        if (ng->elements[i] == NULL) {
            perror("Cannot allocate memory for new grid row.");
        
            exit(EXIT_FAILURE);
        }
    }
    
    ng->size = grid_size;
    
    for (int i = 0; i < TOTAL_SHIPS; i++) {
        ng->ships[i] = NULL;
    }

    return ng;
}

void water_grid(struct grid *gd) {
    int size = gd->size;
    
    /* Fill the grid with water */
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            gd->elements[i][j] = WATER;
        }
    }
}

void ships_grid(struct grid *gd) {
    /* Fill the grid with water */
    water_grid(gd);
    
    int posx_start = -1;
    int posy_start = -1;
    
    /* Seed */
    srand(time(NULL));
    
    int count = 0;
     
    /* Add one carrier */
    for (int i = 0; i < CARRIERS; i++) {
        struct ship *nc = new_ship(CARRIER_TYPE, CARRIER_SIZE);
        place_ship(gd, nc, posx_start, posy_start);
        
        gd->ships[count] = nc;
    
        count++;
    }
    
    /* Add one battleship */
    for (int i = 0; i < BATTLESHIPS; i++) {
        struct ship *nb = new_ship(BATTLESHIP_TYPE, BATTLESHIP_SIZE);
        place_ship(gd, nb, posx_start, posy_start);
        
        gd->ships[count] = nb;
    
        count++;
    }
    
     /* Add two frigates */
    for (int i = 0; i < FRIGATES; i++) {
        struct ship *nf = new_ship(FRIGATE_TYPE, FRIGATE_SIZE);
        place_ship(gd, nf, posx_start, posy_start);
        
        gd->ships[count] = nf;
    
        count++;
    }
}

int place_available(struct grid *gd, struct ship *sp, int posx, int posy, int horizontal) {
    int enabled = 1;
    
    if (horizontal) {
        for (int j = 0; j < sp->size; j++) {
            if (!valid_position(gd, posx, posy + j) || gd->elements[posx][posy + j] != WATER) {
                enabled = 0;
                break;
            }
        }
    } else {
        for (int i = 0; i < sp->size; i++) {
            if (!valid_position(gd, posx + i, posy) || gd->elements[posx + i][posy] != WATER) {
                enabled = 0;
                break;
            }
        }
    }
    
    return enabled;
}

void place_ship(struct grid *gd, struct ship *sp, int posx, int posy) {
    int horizontal = 0;
    
    do {
        posx = rand() % gd->size;
        posy = rand() % gd->size;
        
        /* Randomly decide orientation: 0 for vertical, 1 for horizontal */
        horizontal = rand() % 2;
    } while (!place_available(gd, sp, posx, posy, horizontal));
    
    if (horizontal) {
        /* Place ship horizontally */
        for (int j = 0; j < sp->size; j++) {
            gd->elements[posx][posy + j] = sp->type;
        }
    } else {
        /* Place ship vertically */
        for (int i = 0; i < sp->size; i++) {
            gd->elements[posx + i][posy] = sp->type;
        }
    }
}

int valid_position(const struct grid *gd, int posx, int posy) {
    int posx_valid = (0 <= posx) && (posx < gd->size);
    int posy_valid = (0 <= posy) && (posy < gd->size);
    
    return posx_valid && posy_valid;
}

void set_value_at(struct grid *gd, int pos_x, int pos_y, char value) {
    gd->elements[pos_x][pos_y] = value;
}

void print_grid(const struct grid *gd) {
    int size = gd->size;
    
    /* Initial column header padding */
    printf("%4c", ' ');
    
    /* Format and print column headers */
    for (int i = 0; i < size; i++) {
        printf((i == size - 1) ? "%2c\n" : "%2c", 'A' + i);
    }
    
    /* Initial column delimiter padding */
    printf("%3c+", ' ');
    
    /* Format and print column delimiter */
    for (int i = 0; i < size; i++) {
        printf((i == size - 1) ? "--\n" : "--");
    }
    
    /* Format and print row number, delimiter and corresponding grid element */
    for (int i = 0; i < size; i++) {
        printf("%2i | ", i + 1);
        
        for (int j = 0; j < size; j++) {
            printf((j == size - 1) ? "%c\n" : "%c ", gd->elements[i][j]);
        }
    }
}

void delete_grid(struct grid *gd) {
    int size = gd->size;
    
    /* Deallocate each ship */
    for (int i = 0; i < TOTAL_SHIPS; i++) {
        if (gd->ships[i] != NULL) {
            delete_ship(gd->ships[i]);
        }
    }
    
    /* Deallocate each row */
    for (int i = 0; i < size; i++) {
        free(gd->elements[i]);
        gd->elements[i] = NULL;
    }
    
    /* Deallocate elements */
    free(gd->elements);
    gd->elements = NULL;
    
    /* Deallocate grid object */
    free(gd);
    gd = NULL;
}