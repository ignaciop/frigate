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

void ships_grid(struct grid *gd) {
    int size = gd->size;
    
    /* Fill the array initial values */
    /* Locate ships properly */
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int index = rand() % 4;
            
            gd->elements[i][j] = ELEMS_VALUES[index];
        }
    }
}

void user_grid(struct grid *gd) {
    int size = gd->size;
    
    /* Fill the user grid with initial values */
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            gd->elements[i][j] = ELEMS_VALUES[0];
        }
    }
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