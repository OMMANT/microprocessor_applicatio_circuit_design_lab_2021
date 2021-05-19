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
    map.y = 6;
    map.current_block = rand() % N_BLOCK;
    map.next_block = rand() % N_BLOCK;
    printf("current_block: %d\n", map.current_block);
    for(int i = 0; i < 4; i++){
        map.block_position[0][i] = blocks[map.current_block][0][i] + map.y;
        map.block_position[1][i] = blocks[map.current_block][1][i] + map.x;
        printf("(y, x): (%d, %d)\n", map.block_position[0][i], map.block_position[1][i]);
    }
}

void map_print(){
    for(int i = ROW - 1; i >= 0; i--){
        for(int j = 0; j < COL; j++){
            printf("(%d, %d): %d ", i, j, map.map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void map_refresh(){
    for(int i = 0; i < 4; i++){
        int x, y;
        y = map.block_position[0][i];
        x = map.block_position[1][i];

        if(!((0 <= x && x < COL) && (0 <= y && y < ROW)))
            continue;

        if(map.map[y][x] == 0) // Available
            map.map[y][x] = 1;
        else{
            ;
            //Unabailable;
        }       
    }
}

void map_block_down(){
    map.y--;
    boolean is_stop = FALSE;
    for(int i = 0; i < 4; i++){
        int *y = &map.block_position[0][i];
        int *x = &map.block_position[1][i];
        map.map[*y][*x] = 0;
        printf("MAP_BLOCK_DOWN1 (y, x): (%d, %d)\n", *y, *x);
        *y = blocks[map.current_block][0][i] + map.y;
        *x = blocks[map.current_block][1][i] + map.x;
        printf("MAP_BLOCK_DOWN2 (y, x): (%d, %d)\n", map.block_position[0][i], map.block_position[1][i]);
        if(*y == -1){
            *y = 0;
            is_stop = TRUE;
        }
    }
    
    if(is_stop){
        for(int i = 0; i < 4; i++){
            int y = map.block_position[0][i];
            int x = map.block_position[1][i];
            map.map[y][x] = 1;
        }
        map.current_block = map.next_block;
        map.next_block = rand() % N_BLOCK;
        map.x = 2;
        map.y = 6;
        printf("current_block: %d\n", map.current_block);
        for(int i = 0; i < 4; i++){
            map.block_position[0][i] = blocks[map.current_block][0][i] + map.y;
            map.block_position[1][i] = blocks[map.current_block][1][i] + map.x;
            printf("(y, x): (%d, %d)\n", map.block_position[0][i], map.block_position[1][i]);
        }
    }
}