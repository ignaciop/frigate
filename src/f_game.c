#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "f_game.h"

int play_game(struct grid *sg, struct grid *ug, int shells) {
    int game_res = 0;
    
    print_grid(ug);
    
    char pos[] = " ";
    
    printf("Enter the coordinate for your shot (%d shots remaining): ", shells);
    scanf("%2s", &pos);
    //valid_input(pos[0], pos[1])
    printf("%c - %c\n", pos[0], pos[1]);
    
    
    printf("%s\n", "Here is the original ship locations.");
    print_grid(sg);
    
    return game_res;
}


int valid_input(char c1, char c2) {
    return 0;
}
