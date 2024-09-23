#include <stdio.h>
#include <stdlib.h>

#include "f_game.h"

int main(void) {
    printf("%s\n\n", "Welcome to Frigate!");
    
    char again[1] = "y";
    int games_won = 0;
    int total_games = 0;
    
    do {
        /* Game set-up */
        printf("%s", "How large should I make the grid? ");
        int grid_size = 0;
        
        int n = 0;
        
        while ((n = scanf("%d", &grid_size)) == 0) {
            /* Clear what is left */
            scanf("%*[^\n]");
            
            printf("\n%s", "Please enter a number! How large should I make the grid? ");
        }


        if (grid_size < MIN_GRID_SIZE) {
            printf("The minimum grid size is %d... I'll create one that size.\n", MIN_GRID_SIZE);
    
            grid_size = MIN_GRID_SIZE;
        } else if (grid_size > MAX_GRID_SIZE) {
            printf("The maximum grid size is %d... I'll create one that size.\n", MAX_GRID_SIZE);
    
            grid_size = MAX_GRID_SIZE;
        }
        
        int shells = (grid_size * grid_size) >> 1;

        /* Set up ships grid (data) and user grid (guesses) */
        struct grid *sg = new_grid(grid_size);
        struct grid *ug = new_grid(grid_size);
        
        ships_grid(sg);
        water_grid(ug);
        
        /* Set up queues for visited positions */
        struct sg_queue *posx_visited = sg_queue_create();
        struct sg_queue *posy_visited = sg_queue_create();

        int pg = play_game(sg, ug, shells, posx_visited, posy_visited);
        total_games++;
        
        if (pg) {
            games_won++;
        }
        
        sg_queue_destroy(&posx_visited);
        sg_queue_destroy(&posy_visited);
               
        delete_grid(sg);
        delete_grid(ug);
        
        printf("%s", "Play again (y/N)? ");
        scanf("%1s%*[^\n]", again);
    } while (again[0] == 'y' || again[0] == 'Y');
    
    printf("You won %d out of %d games.\n\n", games_won, total_games);
    printf("%s\n\n", "Thanks for playing!");

    return EXIT_SUCCESS;
}