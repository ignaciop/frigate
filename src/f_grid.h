#ifndef F_GRID_H
#define F_GRID_H

struct grid {
    int size;
    int **elements;
};

struct grid *new_grid(int grid_size);
void init_grid(struct grid *gd);
void print_grid(const struct grid *gd);
void delete_grid(struct grid *gd);

#endif