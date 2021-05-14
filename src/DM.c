#include "DM.h"

void print_map(){
    for(int i = ROW - 1; i >= 0; i--){
        for(int j = COL - 1; j >= 0; j--){
            if(map[i][j] == 1)
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }
}

void init_DM(){
    current_block = rand() % N_BLOCK_TYPE; 
    next_block = rand() % N_BLOCK_TYPE;
    printf("current_block: %d\nnext_block: %d\n", current_block, next_block);
}

