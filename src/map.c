#include "map.h"

void map_init(){
    // BLOCKS SETUP //
    int *block_addr[5] = {(int*)square_block, (int*)cross_block, (int*)jmino_block, (int*)lmino_block, (int*)straight_block};
    for(int i = 0; i < 5; i++){
        blocks[i] = (int**)malloc(sizeof(int*) * 4);
        for(int j = 0; j < 4; j++)
            blocks[i][j] = block_addr[i] + 2 * j;
    }

    // Map Setup //
    map = (Map*)calloc(1, sizeof(Map));
    map->current_block = (Block*)calloc(1, sizeof(Block));
    map->current_block->type = rand() % N_BLOCK;
    copy_block(map->current_block->position, map->current_block->type);    
    map->current_block->y = 6;
    map->current_block->x = 2;
    map->next_block = rand() % N_BLOCK;
    
    map_refresh();
    map_print();
}

void map_print(){
    int (*map_)[COL] = map->map;

    for(int i = ROW - 1; i >= 0; i--){
        for(int j = 0; j < COL; j++){
            printf("%d ", map_[i][j]);
        }
        printf("\n");
    }
    printf("floor: ");
    for(int i = 0; i < COL; i++)
        printf("%d ", map->floor[i]);
    printf("\n");
}

void map_block_down(){
    Block* b = map->current_block;
    int (*map_)[COL] = map->map, y = b->y, x = b->x;

    for(int i = 0; i < 4; i++){
        int y_ = b->position[i][0] + y;
        int x_ = b->position[i][1] + x;

        if((0 <= x_ && x_ < COL) && (0 <= y_ && y_ < ROW)){
            map->map[y_][x_] = 0;
        }
    }
    (b->y)--;
}

void map_refresh(){
    Block *b = map->current_block;
    int (*map_)[COL] = map->map, y = b->y, x = b->x;
    boolean is_stop = FALSE;

    for(int i = 0; i < 4; i++){
        int y_ = b->position[i][0] + y;
        int x_ = b->position[i][1] + x;
        if(y_ >= ROW)
            continue;
        else if(map->floor[x_] == y_)
            is_stop = TRUE;
        
        if(map_[y_][x_] == 0)
            map_[y_][x_] = 1;
        else{
            printf("Game Over!\n");
            exit(0);
        }
    }
    if(is_stop)
        block_stop();
}

void block_stop(){
    Block *b = map->current_block;
    int (*map_)[COL] = map->map, y = b->y, x = b->x;

    for(int i = 0; i < 4; i++){
        int y_ = b->position[i][0] + y;
        int x_ = b->position[i][1] + x;

        map->floor[x_] = y_ + 1;
    }

    free(map->current_block);
    map->current_block = (Block*)malloc(sizeof(Block));
    map->current_block->type = map->next_block;
    copy_block(map->current_block->position, map->current_block->type);
    map->current_block->x = 2;
    map->current_block->y = 6;
    map->next_block = rand() % N_BLOCK;
}

void copy_block(int (*block)[2], BLOCK_TYPE type){
    for(int i = 0; i < 4; i++){
        block[i][0] = blocks[type][i][0];
        block[i][1] = blocks[type][i][1];
    }
}

void block_rotate_left(){
    Block* b = map->current_block;
    int rot[2][2] = {
        {0, -1},
        {1, 0}
    };
    int (*block)[2] = b->position;
    int temp[4][2] = {0,};
    int y = b->y, x = b->x;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                temp[i][j] += block[i][k] * rot[k][j];
            }
        }
    }
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            int y_ = b->position[i][0] + y;
            int x_ = b->position[i][1] + x;
            map->map[y_][x_] = 0;
            block[i][j] = temp[i][j];
        }
    }
}

void block_rotate_right(){
    Block* b = map->current_block;
    int rot[2][2] = {{0, 1}, {-1, 0}}, temp[4][2] = {0, }, (*block)[2] = b->position;
    int y = b->y, x = b->x;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++)
                temp[i][j] += block[i][k] * rot[k][j];
        }
    }
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            int y_ = b->position[i][0] + y;
            int x_ = b->position[i][1] + x;
            map->map[y_][x_] = 0;
            block[i][j] = temp[i][j];
        }
    }
}

void block_move_left(){
    Block* b = map->current_block;
    int (*block)[2] = b->position;
    int y = b->y, x = b->x, min_x = COL;
    boolean move_left = TRUE;

    // 기존에 맵에 그렸던 블럭을 지움
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            int y_ = block[i][0] + y;
            int x_ = block[i][1] + x;
            map->map[y_][x_] = 0;
        }
    }

    for(int i = 0; i < 4; i++){
        int x_ = block[i][1] + x;

        if(!(0 < x_ && x_ < COL))
            move_left = FALSE;
    }

    if(move_left)
        (b->x)--;
}

void block_move_right(){
    Block* b = map->current_block;
    int (*block)[2] = b->position;
    int y = b->y, x = b->x, min_x = COL;
    boolean move_right = TRUE;

    // 기존에 맵에 그렸던 블럭을 지움
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            int y_ = block[i][0] + y;
            int x_ = block[i][1] + x;
            map->map[y_][x_] = 0;
        }
    }

    for(int i = 0; i < 4; i++){
        int x_ = block[i][1] + x;

        if(!(0 <= x_ && x_ < COL - 1))
            move_right = FALSE;
    }

    if(move_right)
        (b->x)++;

}