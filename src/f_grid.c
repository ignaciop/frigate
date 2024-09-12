#include <stdio.h>
#include <stdlib.h>

#include "f_grid.h"

struct grid *new_grid(int grid_size) {
    struct grid *ng = (struct grid *)malloc(sizeof(struct grid));
    
    if (ng == NULL) {
        perror("Cannot allocate memory for new grid object.");
        
        exit(EXIT_FAILURE);
    }
    
    /* Allocate a 1 x grid_size array to hold pointers to more arrays */
    
    char **elements = (char **)malloc(sizeof(char *) * grid_size);
    
    if (elements == NULL) {
        perror("Cannot allocate memory for new grid.");
        
        exit(EXIT_FAILURE);
    }
    
    /* Allocate each row in that column */
    
    for (int i = 0; i < grid_size; i++) {
        elements[i] = (char *)malloc(sizeof(char) * grid_size);
        
        if (elements[i] == NULL) {
            perror("Cannot allocate memory for new grid row.");
        
            exit(EXIT_FAILURE);
        }
    }
    
    ng->size = grid_size;
    ng->elements = elements;
    
    return ng;
}

void init_grid(struct grid *gd) {
    int size = gd->size;
    
    /* Fill the array initial values */
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int index = rand() % 3;
            
            (gd->elements)[i][j] = SHIP_TYPES[index];
        }
    }
}

void print_grid(const struct grid *gd) {
    int size = gd->size;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf((j == size - 1) ? "%c\n" : "%c ", (gd->elements)[i][j]);
        }
    }
}

void delete_grid(struct grid *gd) {
    int size = gd->size;
    
    /* Deallocate each row */
    for (int i = 0; i < size; i++) {
        free((gd->elements)[i]);
        (gd->elements)[i] = NULL;
    }
    
    /* Deallocate elements */
    free(gd->elements);
    gd->elements = NULL;
    
    /* Deallocate grid object*/
    free(gd);
    gd = NULL;
}