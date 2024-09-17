#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "f_game.h"

int play_game(struct grid *sg, struct grid *ug, int shells) {
    int game_res = 0;
    
    print_grid(ug);
    
    char pos[2] = "  ";
    
    do {
        printf("Enter the coordinate for your shot (%d shots remaining): ", shells);
        scanf("%2s%*[^\n]", pos);
    } while(!valid_input(ug, pos[0], pos[1]));
    
    printf("%c%c%c\n", pos[0], pos[1]);
    
    
    printf("%s\n", "Here is the original ship locations.");
    print_grid(sg);
    
    return game_res;
}


int valid_input(struct grid *gd, char c1, char c2) {
    int cond1 = isalpha(c1) && isdigit(c2);
    int cond2 = isalpha(c2) && isdigit(c1);
    
    int posx = -1;
    int posy = -1;
    
    if (cond1) {
        posx = (c2 - '0') - 1;
        posy = toupper(c1) - 'A';
    } else if (cond2) {
        posx = (c1 - '0') - 1;
        posy = toupper(c2) - 'A';
    }
    
    int vd = valid_position(gd, posx, posy);
    
    return vd;
}
