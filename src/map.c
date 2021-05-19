#include "map.h"

void map_init(){
    for(int i = 0; i < 5; i++)
        blocks[i] = (int**)malloc(sizeof(int*) * 4);
    blocks[0][0] = square_block;
    blocks[0][1] = square_block + 1;
    blocks[1][0] = cross_block;
    blocks[1][1] = cross_block + 1;
    blocks[2][0] = jmino_block;
    blocks[2][1] = jmino_block + 1;
    blocks[3][0] = lmino_block;
    blocks[3][1] = lmino_block + 1;
    blocks[4][0] = straight_block;
    blocks[4][1] = straight_block + 1;

    map.x = 2;
    map.y = 7;
    map.current_block = rand() % N_BLOCK;
    for(int i = 0; )
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            map.block_position[i][j] = blocks[map.current_block][i][j];
            if(i == 0)
                map.block_position[i][j] += map.y;
            else map.block_position[i][j] += map.x;
        }        
    }
}

void map_print(){
    for(int i = ROW - 1; i >= 0; i--){
        for(int j = 0; j < COL; j++){
            printf("%d ", map.map[i][j]);
        }
        printf("\n");
    }
}

void map_refresh(){

}