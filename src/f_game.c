#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "f_game.h"

int play_game(struct grid *sg, struct grid *ug, struct grid *ig, int shots, struct sg_queue *posx_visited, struct sg_queue *posy_visited) {
    int game_res = 0;
    int ships_sunken = 0;
    int rem_shots = shots;
    
    print_grid(ug);
    
    while (rem_shots > 0) {
        char chars_pos[3] = {'0'};
        int nums_pos[2] = {0};
        
        /* Enter alphanumeric coordinates until valid (in grid size range) */
        do {
            printf("Enter the coordinate for your shot (%d %s remaining): ", rem_shots, (rem_shots != 1) ? "shots" : "shot");
            scanf("%3s%*[^\n]", chars_pos); 
        } while(!valid_input(ug, chars_pos, nums_pos));
        
        /* Check if the position was already entered */
        if (repeated(nums_pos, posx_visited, posy_visited)) {
            printf("%s\n\n", "Coordinate already entered!");
            
            continue;
        }

        int hm = is_hit(sg, ug, ig, nums_pos[0], nums_pos[1], &ships_sunken);
        
        printf((chars_pos[2] == ' ') ? "\n%s%s\n" : "\n%s %s\n", chars_pos, (hm) ? "is a hit!" : "is a miss!");
        
        print_grid(ug);
       
        --rem_shots;
        
        if (ships_sunken == TOTAL_SHIPS) {
            /* Game won */
            game_res = 1;
            
            break;
        }
    }
    
    printf("%s\n", "Here is the original ship locations.");
    print_grid(sg);
    
    printf((ships_sunken == 1) ? "You sunk %d ship.\n\n" : "You sunk %d ships.\n\n", ships_sunken);
    
    return game_res;
}

int valid_input(const struct grid *gd, char chars_pos[], int nums_pos[]) {
    /* Posible combinations of valid inputs */
    int cond1 = isalpha(chars_pos[0]) && isdigit(chars_pos[1]);
    int cond2 = isalpha(chars_pos[1]) && isdigit(chars_pos[0]);
    int cond3 = isalpha(chars_pos[0]) && isdigit(chars_pos[1]) && isdigit(chars_pos[2]);
    int cond4 = isdigit(chars_pos[0]) && isdigit(chars_pos[1]) && isalpha(chars_pos[2]);
    
    /* Posible combinations of invalid inputs */
    int cond5 = isdigit(chars_pos[0]) && isalpha(chars_pos[1]) && isalpha(chars_pos[2]);
    int cond6 = isdigit(chars_pos[0]) && isalpha(chars_pos[1]) && isdigit(chars_pos[2]);
    int cond7 = isalpha(chars_pos[0]) && isdigit(chars_pos[1]) && isalpha(chars_pos[2]);
    int cond8 = isalpha(chars_pos[0]) && isalpha(chars_pos[1]) && isalpha(chars_pos[2]);
    int cond9 = isalpha(chars_pos[0]) && isalpha(chars_pos[1]) && isdigit(chars_pos[2]);
    
    int posx = -1;
    int posy = -1;
    
    if (!(cond5 || cond6 || cond7 || cond8 || cond9)) {
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
    } else {
        printf("%s\n\n", "Please enter a valid coordinate!");
    }
    
    int vd = valid_position(gd, posx, posy);
    
    if (vd) {
        nums_pos[0] = posx;
        nums_pos[1] = posy;
        
        organize_input(chars_pos);
    }
    
    return vd;
}

int is_hit(struct grid *sg, struct grid *ug, struct grid *ig, const int posx, const int posy, int *sh_sunken) {
    int hm = 0;
    
    if (sg->elements[posx][posy] != WATER) {
        ug->elements[posx][posy] = HIT;
        
        update_damage(sg, ig, posx, posy, sh_sunken);
        
        hm = 1;
    } else {
        ug->elements[posx][posy] = MISS;
    }
    
    return hm;
}

void update_damage(struct grid *sg, struct grid *ig, const int posx, const int posy, int *sh_sunken) {
    char elem_hitted = sg->elements[posx][posy];
    char id_hitted = ig->elements[posx][posy];
    
    for (int i = 0; i < TOTAL_SHIPS; i++) {
        if (!sg->ships[i]->sunken_fg && sg->ships[i]->type == elem_hitted && sg->ships[i]->id == id_hitted) {
            sg->ships[i]->health--;
            
            if (sg->ships[i]->health == 0) {
                sg->ships[i]->sunken_fg = 1;
                
                (*sh_sunken)++;
            }
            
            break;
        }
    }
}

int repeated(const int nums_pos[], struct sg_queue *posx_visited, struct sg_queue *posy_visited) {
    int is_repeated = 0;
    int qsize = sg_queue_size(posx_visited);
    
    int i = 0;
    
    while (i < qsize) {
        int posxs = value_at(posx_visited, i);
        int posys = value_at(posy_visited, i);
        
        if (nums_pos[0] == posxs && nums_pos[1] == posys) {
            is_repeated = 1;
            
            break;
        }
        
        i++; 
    }
    
    /* Add to queue if is not repeated or first coordinate */
    if (!is_repeated || qsize == 0) {
        sg_queue_enqueue(posx_visited, nums_pos[0]);
        sg_queue_enqueue(posy_visited, nums_pos[1]);
    }
    
    return is_repeated;
}

void organize_input(char chars_pos[]) {
    /* Already sanitized input, from 2 to 3 characters representing a valid position */ 
    /* (i.e.: A1, a1, 1a, 1A, 12a, 12A, A12, a12, a02, 02a, A02, 02A) */
    /* Order output (letter first, number second) */
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