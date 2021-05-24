#ifndef MAP
#define MAP
#define ROW 7
#define COL 5
#define N_BLOCK 5

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#endif

static int square_block[4][2] = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1},
};

static int cross_block[4][2] = {
    {0, 0},
    {0, -1},
    {0, 1},
    {1, 0},
};

static int jmino_block[4][2] = {
    {0, 0},
    {1, -1},
    {0, -1},
    {0, 1},
};

static int lmino_block[4][2] = {
    {0, 0},
    {1, 1},
    {0, -1},
    {0, 1},
};

static int straight_block[4][2] = {
    {0, 0},
    {0, -1},
    {0, 1},
    {0, 2},
};

typedef enum BLOCKS{
    square,
    cross,
    jmino,
    lmino,
    straight
}BLOCK_TYPE;

typedef struct BLOCK{
    BLOCK_TYPE type;
    int position[4][2];
    int x, y;    
}Block;

typedef struct MAP{
    int map[ROW][COL];
    int floor[COL];
    
    Block* current_block;
    BLOCK_TYPE next_block;
}Map;

/* GLOBAL VARIABLES */
Map* map;
int** blocks[5];

/* FUNCTION DECLARATION */
void map_init();
void map_print();
void map_block_down();
void map_refresh();
void block_stop();
void block_rotate_left();
void block_rotate_right();
void block_move_left();
void block_move_right();
void copy_block(int (*block)[2], BLOCK_TYPE type);
