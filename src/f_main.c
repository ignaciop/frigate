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
    
    int shells = (grid_size * grid_size) >> 1;
    
    struct grid *sc = new_grid(grid_size);
    ships_grid(sc);
    
    struct grid *uc = new_grid(grid_size);
    water_grid(uc);
    print_grid(uc);
    
    /*  char again = 'y';
        int games_won = 0;
        int total_games = 0;
        int grid_size = 0;
        
        do {
            printf("%s", "How large should I make the grid? ");
            scanf("%d", &grid_size);
    
            if (grid_size < MIN_GRID_SIZE) {
                printf("The minimum grid size is %d... I'll create one that size.\n", MIN_GRID_SIZE);
        
                grid_size = MIN_GRID_SIZE;
            } else if (grid_size > MAX_GRID_SIZE) {
                printf("The maximum grid size is %d... I'll create one that size.\n", MAX_GRID_SIZE);
        
                grid_size = MAX_GRID_SIZE;
            }
            
            int shells = (grid_size * grid_size) >> 1;
    
            struct grid *sc = new_grid(grid_size);
            ships_grid(sc);
    
            struct grid *uc = new_grid(grid_size);
            water_grid(uc);
            
            int pg = play_game(sc, uc, shells);
            
            if (pg) {
                games_won++;
            }
            total_games++;
            
            printf("%s\n", "Here is the original ship locations.");
            print_grid(sc);
            delete_grid(sc);
            delete_grid(uc);
            
            printf("Play again (y/N)? %c", again);
        } while (again == 'y' || again == 'Y');
        
        printf("You won %d of %d games.\n\n", won_games, total_games);
        printf("%s\n\n", "Thanks for playing!");
    
    */
    char pos[] = " ";
    
    printf("Enter the coordinate for your shot (%d shots remaining): ", shells);
    scanf("%2s", &pos);
    //valid_input(pos[0], pos[1])
    printf("%c - %c\n", pos[0], pos[1]);
    
    
    printf("%s\n", "Here is the original ship locations.");
    print_grid(sc);
    delete_grid(sc);
    
    
    delete_grid(uc);

    return EXIT_SUCCESS;
}