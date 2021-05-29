#include "block.h"
#include "map.h"
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

void stuck_map(Block* b){
    Map* map = get_map();
    int (*map_arr)[COL] = map->map;
    
    for(int i = 0; i < 4; i++){
        int x = b->position[i][0] + b->x;
        int y = b->position[i][1] + b->y;

        map_arr[y][x] = 1;
    }
    map->current_block = get_block(map->next_block_type);
    map->next_block_type = rand() % N_BLOCK;
}

void move_down(Block* b){
    b->y--;
}

boolean can_move_down(){
    Map* map = get_map();
    Block* block = map->current_block;
    int* floor = map->floor;
    int base_x = block->x, base_y = block->y;

    for(int i = 0; i < 4; i++){
        int x = block->position[i][0] + base_x;
        int y = block->position[i][1] + base_y;

        if(floor[x] >= y){
            return FALSE;
        }
    }
    return TRUE;
}

void rotate_left(Block* b){
	int rot[2][2] = {{0, 1}, {-1, 0}};
	int temp_arr[4][2] = {0, };

	for(int i = 1; i < 4; i++){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 2; k++){
				temp_arr[i][j] += b->position[i][k] * rot[k][j];
			}
		}
	}

	for(int i = 0; i < 4; i++){
		b->position[i][0] = temp_arr[i][0];
		b->position[i][1] = temp_arr[i][1];
	}

	check_validation(b);
}

void rotate_right(Block* b){
	int rot[2][2] = {{0, -1}, {1, 0}};
	int temp_arr[4][2] = {0, };

	for(int i = 1; i < 4; i++){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 2; k++)
				temp_arr[i][j] += b->position[i][k] * rot[k][j];
		}
	}

	for(int i = 0; i < 4; i++){
		b->position[i][0] = temp_arr[i][0];
		b->position[i][1] = temp_arr[i][1];
	}
	check_validation(b);
}

void move_left(Block* b){
	Map* map = get_map();
	int base_x = b->x, base_y = b->y;
	int min_x = base_x;
	boolean movable = TRUE;

	for(int i = 1; i < 4; i++){
		int x = b->position[i][0] + base_x, y = b->position[i][1] + base_y;
		min_x = min(min_x, x);
		if((0 < x && x < COL) && (y < ROW) && map->map[y][x - 1] == 1){
			movable = FALSE;
			break;
		}
	}

	if(0 < min_x && movable){
		b->x--;
	}
}

void move_right(Block* b){
	Map* map = get_map();
	int base_x = b->x, base_y = b->y;
	int max_x = base_x;
	boolean movable = TRUE;

	for(int i = 1; i <4; i++){		
		int x = b->position[i][0] + base_x, y = b->position[i][1] + base_y;
		max_x = max(max_x, x);
		if((0 <= x && x < COL - 1) && (y < ROW) && map->map[y][x + 1] == 1){
			movable = FALSE;
			break;
		}
	}

	if(max_x < 4 && movable){
		b->x++;
	}
}

void check_validation(Block* b){
	int base_x = b->x, base_y = b->y;

	// 1) base_x < 0 or base_x >= COL
	if(base_x < 0)
		b->x++;
	else if(base_x >= COL)
		b->x--;

	// 2) x < 0 or x >= COL
	int min_x = COL, max_x = 0;
	for(int i = 0; i < 4; i++){
		int x = b->position[i][0] + base_x;
		min_x = min(min_x, x);
		max_x = max(max_x, x);
	}
	if(min_x < 0)
		b->x += (-1 * min_x);
	else if(max_x >= COL)
		b->x -= (max_x - (COL - 1));	
}

void block_descent(Block* b, int* floor){
	int move_y = ROW;
	int base_x = b->x, base_y = b->y;

	for(int i = 0; i < 4; i++){
		int x = b->position[i][0] + base_x;
		int y = b->position[i][1] + base_y;
		int move = y - floor[x];

		move_y = min(move_y, move);
	}

	b->y -= move_y;
}