#include "map.h"
#include <stdlib.h>

void map_init(){

}

Map* get_map(){
    Map* ptr = (Map*)calloc(1, sizeof(Map));

    ptr->current_block = get_block(rand() % N_BLOCK);
    ptr->next_block_type = rand() % N_BLOCK;

}