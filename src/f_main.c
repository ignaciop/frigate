#include <stdio.h>
#include <stdlib.h>

#include "f_grid.h"

#define MIN_GRID_SIZE 5
#define MAX_GRID_SIZE 20

int main(int argc, char *argv) {
    printf("%s\n\n", "Welcome to Frigate!");
    
    printf("%s", "How large should I make the grid? ");
    
    /* Set-up variables */
    int grid_size = 0;
    scanf("%d", &grid_size);
    
    if (grid_size < MIN_GRID_SIZE) {
        printf("The minimum grid size is %d... I'll create one that size.\n", MIN_GRID_SIZE);
        
        grid_size = MIN_GRID_SIZE;
    } else if (grid_size > MAX_GRID_SIZE) {
        printf("The maximum grid size is %d... I'll create one that size.\n", MAX_GRID_SIZE);
        
        grid_size = MAX_GRID_SIZE;
    }
    
    //int shells = grid_size >> 1;
    
    struct grid *sc = new_grid(grid_size);
    
    ships_grid(sc);
    print_grid(sc);
    delete_grid(sc);
    
    /*struct grid *uc = new_grid(grid_size);
    
    user_grid(uc);
    print_grid(uc);*/
    
    /*set_value_at(uc, uc->size - 1, uc->size - 2, 'm');
    print_grid(uc);
    
    delete_grid(uc);*/

    return EXIT_SUCCESS;
}