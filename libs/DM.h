#ifndef DOT_MATRIX
#define DOT_MATRIX
#define N_BLOCK_TYPE    5
#define ROW 7
#define COL 5
#include "main.h"

enum Blocks{
    Square,
    Cross,
    L,
    r,
    straight
};

int* block[2][4]={
    {
        {0, 1, 0, 1},
        {0, 0, -1, -1}
    },
    {
        {0, -1, 1, 0},
        {0, 0, 0, 1}
    },
    {
        {0, 0, 1, 2},
        {0, 1, 0, 0}
    },
    {
        {0, 0, -1, -2},
        {0, 1, 0, 0}
    },
    {
        {0, -1, 1, 2},
        {0, 0, 0, 0}
    }
};

static int map[ROW][COL] = {0,};

int new_block;
int current_point[2] = {3, 6};
enum Blocks current_block;
enum Blocks next_block;

void print_map();
void init_DM();


#endif
