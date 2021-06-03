#include "block.h"
#include "map.h"
#include <stdlib.h>

void block_init(){	// 블럭의 기본 초기화 함수
    blocks[0] = (int*)SQUARE_BLOCK;
    blocks[1] = (int*)CROSS_BLOCK;
    blocks[2] = (int*)J_BLOCK;
    blocks[3] = (int*)L_BLOCK;
    blocks[4] = (int*)STRAIGHT_BLOCK;
}

Block* get_block(int type){ // 초기화된 블럭 반환
    Block* ptr = (Block*)malloc(sizeof(Block));
    
    copy(blocks[type], (int*)ptr->position, 8);

    ptr->x = 2;
    ptr->y = 6;

    return ptr;
}

void stuck_map(Block* b){	// 블럭이 바닥에 닿은 이후 블럭을 맵에 고정시키고 다음 블럭으로 넘어가는 함수
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

void move_down(Block* b){	// 블럭을 아래로 한 칸 옮기는 함수
    b->y--;
}

boolean can_move_down(){	// 블럭을 아래로 한 칸 움직일 수 있는지 확인하는 함수
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

void rotate_left(Block* b){	// 블럭을 왼쪽으로 90도 회전시키는 함수
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

void rotate_right(Block* b){	// 블럭을 오른쪽으로 90도 회전시키는 함수
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

void move_left(Block* b){	// 블럭을 왼쪽으로 옮기는 함수
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

void move_right(Block* b){	// 블럭을 오른쪽으로 옮기는 함수
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

void check_validation(Block* b){	//블럭의 위치 유효성을 확인하고 조정하는 함수
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

void block_descent(Block* b, int* floor){	// 블럭을 최대한 아래로 옮기는 함수
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