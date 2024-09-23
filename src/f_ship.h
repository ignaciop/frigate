#ifndef F_SHIP_H
#define F_SHIP_H

#define CARRIER_TYPE 'c'
#define BATTLESHIP_TYPE 'b'
#define FRIGATE_TYPE 'f'

#define CARRIER_SIZE 5
#define BATTLESHIP_SIZE 4
#define FRIGATE_SIZE 2

struct ship {
    char type;
    int size;
    int health;
    int sunken_fg;
};

struct ship *new_ship(const char s_type, const int s_size);
void delete_ship(struct ship *sp);

#endif