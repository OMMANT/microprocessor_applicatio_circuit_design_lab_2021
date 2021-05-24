#ifndef MAP_H
#define MAP_H
#define ROW 7
#define COL 5
#define N_BLOCK 5

#include "utils.h"
#include "block.h"

/* ABSTRACT DATA TYPE DEFINITION */
typedef struct MAP{
    int map[ROW][COL];
    int floor[COL];

    Block* current_block;
    Type next_block_type;
}Map;

/* ABSTRACT FUNCTION DEFINITION */
void map_init();
Map* get_map();

/* GLOBAL VARIABLE */

#endif