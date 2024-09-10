#include <stdio.h>
#include <stdlib.h>

#include "f_constants.h"

int main(int argc, char *argv) {
    printf("%s\n\n", "Welcome to Frigate!");
    printf("%s", "How large should I make the grid? ");
    
    /* Set-up variables */
    
    int grid_size = 0;
    scanf("%d", &grid_size);
    
    if (grid_size < MIN_GRID_SIZE || grid_size > MAX_GRID_SIZE) {
        printf("The minimum grid size is %d... I'll create one that size.\n", MIN_GRID_SIZE);
        
        grid_size = MIN_GRID_SIZE;
    }
    
    int shells = grid_size >> 1;
    
    printf("%d x %d, %d shells\n", grid_size, grid_size, shells);

    return EXIT_SUCCESS;
}