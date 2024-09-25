#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "f_grid.h"

struct grid *new_grid(const int grid_size) {
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
    
    ng->ships_sunken = 0;

    return ng;
}

void ids_grid(struct grid *gd) {
    /* Fill the grid with 'X', to accomodate ship ids */
    for (int i = 0; i < gd->size; i++) {
        for (int j = 0; j < gd->size; j++) {
            gd->elements[i][j] = 'X';
        }
    }
}

void water_grid(struct grid *gd) {
    /* Fill the grid with water */
    for (int i = 0; i < gd->size; i++) {
        for (int j = 0; j < gd->size; j++) {
            gd->elements[i][j] = WATER;
        }
    }
}

void data_grid(struct grid *gd, struct grid *ig) {
    /* Fill the ship grid with water */
    water_grid(gd);
    
    /* Fill the ship id grid with 'X' */
    ids_grid(ig);
    
    int posx_start = -1;
    int posy_start = -1;
    
    /* Seed for random numbers */
    srand(time(NULL));
    
    int count = 0;
     
    /* Add one carrier */
    for (int i = 0; i < CARRIERS; i++) {
        struct ship *nc = new_ship(CARRIER_TYPE, CARRIER_SIZE);
        nc->id = count + '0';
        
        place_ship(gd, ig, nc, posx_start, posy_start);
        
        gd->ships[count] = nc;
    
        ++count;
    }
    
    /* Add one battleship */
    for (int i = 0; i < BATTLESHIPS; i++) {
        struct ship *nb = new_ship(BATTLESHIP_TYPE, BATTLESHIP_SIZE);
        nb->id = count + '0';
        
        place_ship(gd, ig, nb, posx_start, posy_start);
        
        gd->ships[count] = nb;
    
        ++count;
    }
    
     /* Add two frigates */
    for (int i = 0; i < FRIGATES; i++) {
        struct ship *nf = new_ship(FRIGATE_TYPE, FRIGATE_SIZE);
        nf->id = count + '0';
        
        place_ship(gd, ig, nf, posx_start, posy_start);
        
        gd->ships[count] = nf;
    
        ++count;
    }
}

int place_available(const struct grid *gd, const struct ship *sp, const int posx, const int posy, const int orientation) {
    int enabled = 1;
    
    if (orientation) {
        /* Orientation = 1 (Horizontal) */
        for (int j = 0; j < sp->size; j++) {
            if (!valid_position(gd, posx, posy + j) || gd->elements[posx][posy + j] != WATER) {
                enabled = 0;
                break;
            }
        }
    } else {
        /* Orientation = 0 (Vertical) */
        for (int i = 0; i < sp->size; i++) {
            if (!valid_position(gd, posx + i, posy) || gd->elements[posx + i][posy] != WATER) {
                enabled = 0;
                break;
            }
        }
    }
    
    return enabled;
}

void place_ship(struct grid *gd, struct grid *ig, const struct ship *sp, int posx, int posy) {
    int orientation = 0;
    
    do {
        posx = rand() % gd->size;
        posy = rand() % gd->size;
        
        /* Randomly decide orientation: 0 for vertical, 1 for horizontal */
        orientation = rand() % 2;
    } while (!place_available(gd, sp, posx, posy, orientation));
    
    if (orientation) {
        /* Place ship horizontally */
        for (int j = 0; j < sp->size; j++) {
            gd->elements[posx][posy + j] = sp->type;
            ig->elements[posx][posy + j] = sp->id;
        }
    } else {
        /* Place ship vertically */
        for (int i = 0; i < sp->size; i++) {
            gd->elements[posx + i][posy] = sp->type;
            ig->elements[posx + i][posy] = sp->id;
        }
    }
}

int valid_position(const struct grid *gd, const int posx, const int posy) {
    int posx_valid = (0 <= posx) && (posx < gd->size);
    int posy_valid = (0 <= posy) && (posy < gd->size);
    
    return posx_valid && posy_valid;
}

void print_grid(const struct grid *gd) {
    printf("\n");
    
    /* Initial column header padding */
    printf("%4c", ' ');
    
    /* Format and print column headers */
    for (int i = 0; i < gd->size; i++) {
        printf((i == gd->size - 1) ? "%2c\n" : "%2c", 'A' + i);
    }
    
    /* Initial column delimiter padding */
    printf("%3c+", ' ');
    
    /* Format and print column delimiter */
    for (int i = 0; i < gd->size; i++) {
        printf((i == gd->size - 1) ? "--\n" : "--");
    }
    
    /* Format and print row number, delimiter and corresponding grid element */
    for (int i = 0; i < gd->size; i++) {
        printf("%2i | ", i + 1);
        
        for (int j = 0; j < gd->size; j++) {
            char element = gd->elements[i][j];
            char color_pf[8] = {'0'};
            
            switch (element) {
                case WATER:
                    strncpy(color_pf, WATER_COLOR, 8);
                    break;
                case HIT:
                    strncpy(color_pf, HIT_COLOR, 8);
                    break;
                case MISS:
                    strncpy(color_pf, MISS_COLOR, 8);
                    break;
                case CARRIER_TYPE:
                    strncpy(color_pf, CARRIER_COLOR, 8);
                    break;
                case BATTLESHIP_TYPE:
                    strncpy(color_pf, BATTLESHIP_COLOR, 8);
                    break;
                case FRIGATE_TYPE:
                    strncpy(color_pf, FRIGATE_COLOR, 8);
                    break;
                default:
                    break;
            }

            printf((j == gd->size - 1) ? "%s%c%s\n" : "%s%c%s ", color_pf, element, RESET_COLOR);
        }
    }
    
    printf("\n");
}

void delete_grid(struct grid *gd) { 
    /* Deallocate each ship */
    for (int i = 0; i < TOTAL_SHIPS; i++) {
        if (gd->ships[i] != NULL) {
            delete_ship(gd->ships[i]);
        }
    }
    
    /* Deallocate each row */
    for (int i = 0; i < gd->size; i++) {
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