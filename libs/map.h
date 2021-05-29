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
    int erasable[ROW];
    int erasable_count, score, combo;
    boolean erased_before;

    Block* current_block;
    Type next_block_type;
}Map;

/* ABSTRACT FUNCTION DEFINITION */
void map_init();
void map_print();
void bind_block();
void unbind_block();
void floor_rise();
void check_erasable();
void erase();
Map* get_map();
boolean can_floor_rise();

/* GLOBAL VARIABLE */
Map* map;

#endif