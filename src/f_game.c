#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "f_game.h"

int play_game(struct grid *sg, struct grid *ug, int shots) {
    int game_res = 0;
    //int shots = shells;
    
    while (shots > 0) {
        print_grid(ug);

        char chars_pos[3] = "   ";
        int nums_pos[2] = {0};

        /* Enter alphanumeric coordinates until valid (in grid size range) */
        do {
            printf("Enter the coordinate for your shot (%d %s remaining): ", shots, (shots != 1) ? "shots" : "shot");
            scanf("%3s%*[^\n]", chars_pos);
        } while(!valid_input(ug, chars_pos, nums_pos));

        int hm = is_hit(sg, ug, nums_pos[0], nums_pos[1]);

        printf("\n%s %s\n", chars_pos, (hm) ? "is a hit!" : "is a miss!");
       
        shots--;
    }
    
    printf("%s\n", "Here is the original ship locations.");
    print_grid(sg);
    
    return game_res;
}


int valid_input(struct grid *gd, char chars_pos[], int nums_pos[]) {
    /* Posible combinations of valid inputs */
    int cond1 = isalpha(chars_pos[0]) && isdigit(chars_pos[1]);
    int cond2 = isalpha(chars_pos[1]) && isdigit(chars_pos[0]);
    int cond3 = isalpha(chars_pos[0]) && isdigit(chars_pos[1]) && isdigit(chars_pos[2]);
    int cond4 = isdigit(chars_pos[0]) && isdigit(chars_pos[1]) && isalpha(chars_pos[2]);
    
    /* Posible combinations of invalid inputs */
    int cond5 = isdigit(chars_pos[0]) && isalpha(chars_pos[1]) && isalpha(chars_pos[2]);
    int cond6 = isdigit(chars_pos[0]) && isalpha(chars_pos[1]) && isdigit(chars_pos[2]);
    int cond7 = isalpha(chars_pos[0]) && isdigit(chars_pos[1]) && isalpha(chars_pos[2]);
    
    int posx = -1;
    int posy = -1;
    
    if (!(cond5 || cond6 || cond7)) {
        /* Check if alphanumeric inputs are valid and saving them in an array */
        if (cond1 && !cond3 && !cond4) {
            chars_pos[0] = toupper(chars_pos[0]);
            
            posx = (chars_pos[1] - '0') - 1;
            posy = chars_pos[0] - 'A';
        } else if (cond2) {
            chars_pos[1] = toupper(chars_pos[1]);
            
            posx = (chars_pos[0] - '0') - 1;
            posy = chars_pos[1] - 'A';
        } else if (cond3) {
            chars_pos[0] = toupper(chars_pos[0]);
            
            posx = (chars_pos[1] - '0') * 10 + (chars_pos[2] - '0') - 1;
            posy = chars_pos[0] - 'A';
        } else if (cond4) {
            chars_pos[2] = toupper(chars_pos[2]);
            
            posx = (chars_pos[0] - '0') * 10 + (chars_pos[1] - '0') - 1;
            posy = chars_pos[2] - 'A';
        }
    }
    
    int vd = valid_position(gd, posx, posy);
    
    if (vd) {
        nums_pos[0] = posx;
        nums_pos[1] = posy;
        
        swap_chars(chars_pos);
    }
    
    return vd;
}

int is_hit(struct grid *sg, struct grid *ug, int posx, int posy) {
    int hm = 0;
    
    if (sg->elements[posx][posy] != WATER) {
        ug->elements[posx][posy] = HIT;
        
        hm = 1;
    } else {
        ug->elements[posx][posy] = MISS;
    }
    
    return hm;
}

void swap_chars(char chars_pos[]) {
    /* Already sanitized input, from 2 to 3 characters representing a valid position */ 
    /* (i.e.: A1, a1, 1a, 1A, 12a, 12A, A12, a12, a02, 02a, A02, 02A) */
    char c0 = chars_pos[0];
    char c1 = chars_pos[1];
    char c2 = chars_pos[2];
    
    if (isalpha(c0)) {
        if (c1 == '0') {
            chars_pos[1] = c2;
            chars_pos[2] = ' ';
        }
    } else {
        if (isalpha(c1)) {
            chars_pos[0] = c1;
            chars_pos[1] = c0;
        } else {
            chars_pos[0] = c2;
            
            if (c0 == '0') {
                chars_pos[1] = c1;
                chars_pos[2] = ' ';
            } else {
                chars_pos[1] = c0;
                chars_pos[2] = c1;
            }
        }
    }
}
