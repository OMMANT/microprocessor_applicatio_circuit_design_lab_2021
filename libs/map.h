#ifndef MAP
#define MAP
#define ROW 7
#define COL 5
#define N_BLOCK 5

#include <stdlib.h>
#include <stdio.h>

typedef enum BLOCKS{
    square,
    cross,
    jmino,
    lmino
}Blocks;

static int square_block[2][4] ={
    {0, 0, 1, 1},
    {0, 1, 0, 1}
};

static int cross_block[2][4] = {
    {0, 0, 0, 1},
    {0, -1, 1, 0}
};

static int jmino_block[2][4] = {
    {0, 0, 0, 1},
    {0, 1, 2, 0}
};

static int lmino_block[2][4] = {
    {0, 0, 0, 1},
    {0, -2, -1, 0}
};

static int straight_block[2][4] = {
    {0, 0, 0, 0},
    {0, -1, 1, 2}
};

typedef struct MAP{
    int map[ROW][COL];
    int block_position[2][4];
    int x, y;

    Blocks current_block;
    
}Map;

/* GLOBAL VARIABLES */
Map map;
int** blocks[5];

/* FUNCTION DECLARATION */
void map_init();
void map_print();
void map_refresh();

#endif