#ifndef F_GRID_H
#define F_GRID_H

#define ELEMS_VALUES (char[]){'-', 'b', 'c', 'f'}

struct grid {
    int size;
    char **elements;
};

struct grid *new_grid(int grid_size);
void ships_grid(struct grid *gd);
void user_grid(struct grid *gd);
void set_value_at(struct grid *gd, int pos_x, int pos_y, char value);
void print_grid(const struct grid *gd);
void delete_grid(struct grid *gd);

#endif