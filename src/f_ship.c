#include <stdio.h>
#include <stdlib.h>

#include "f_ship.h"

struct ship *new_ship(const char s_type, const int s_size) {
    struct ship *ns = (struct ship *)malloc(sizeof(struct ship));
    
    if (ns == NULL) {
        perror("Cannot allocate memory for new ship object.");
        
        exit(EXIT_FAILURE);
    }
  
    ns->type = s_type;
    ns->size = ns->health = s_size;
    ns->sunken_fg = 0;
    
    return ns;
}

void delete_ship(struct ship *sp) {
    /* Deallocate ship object */
    free(sp);
    sp = NULL;
}