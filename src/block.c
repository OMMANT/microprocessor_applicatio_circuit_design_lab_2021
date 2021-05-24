#include "block.h"
#include <stdlib.h>

void block_init(){
    blocks[0] = (int*)SQUARE_BLOCK;
    blocks[1] = (int*)CROSS_BLOCK;
    blocks[2] = (int*)J_BLOCK;
    blocks[3] = (int*)L_BLOCK;
    blocks[4] = (int*)STRAIGHT_BLOCK;
}

Block* get_block(int type){
    Block* ptr = (Block*)malloc(sizeof(Block));
    
    copy(blocks[type], (int*)ptr->position, 8);

    ptr->x = 2;
    ptr->y = 6;

    return ptr;
}

void move_left(Block* b){
    int min_x = 5;

    for(int i = 0; i < 4; i++)
        min_x = min(min_x, b->position[i][0] + b->x);
    
    if(0 < min_x)  //Movable
        b->x--;    
}