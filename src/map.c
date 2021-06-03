#include "map.h"
#include "dot.h"
#include "led.h"
#include <stdlib.h>
#include <stdio.h>

void map_init(){
    int (*map_arr)[COL] = NULL;    
    map = (Map*)calloc(1, sizeof(Map));
    map->current_block = get_block(rand() % N_BLOCK);
    map->next_block_type = rand() % N_BLOCK;
    map->score = 0;
    map->combo = 0;
    map->erased_before = FALSE;
    map_arr = map->map;

}

void map_print(){
    int (*map_arr)[COL] = map->map;
    int *floor = map->floor;

    for(int i = ROW - 1; i >= 0; i--){
        printf("| ");
        for(int j = 0; j < COL; j++){
            if(map_arr[i][j] == 1)
            printf("* ");
            else printf("  ");
        }
        printf("|\n");
    }
    printf("floor: ");
    for(int i = 0; i < COL; i++){
        printf("%d ", floor[i]);
    }
    printf("\n");
    printf("score: %d\tcombo: %d\tnext_block: %d\n", map->score, map->combo, map->next_block_type);
    dot_write(map_arr);
    led_write(map->combo);
}

void bind_block(){
    // 맵과 블럭을 연결이 유효한 지 확인
    // 1. 블럭 위치에 맵이 비어있어야함
    // 2. 블럭이 유효한 위치에 있어야 함 (0 <= x < col, 0 <= y)
    int (*map_arr)[COL] = map->map;
    Block* block = map->current_block;
    boolean available = TRUE;
    int base_x = block->x, base_y = block->y;

    for(int i = 0; i < 4; i++){
        int x = block->position[i][0] + base_x;
        int y = block->position[i][1] + base_y;

        if(y >= ROW)
            continue;
        // 1. 블럭 위치에 맵이 비어있지 않다면 게임 종료
        if(map_arr[y][x] == 1){
            available = FALSE;
            fprintf(stderr, "Game Over!\nInvalid binding(1)(%d, %d)\n", x, y);
            exit(EXIT_FAILURE);
        }
        // 2. 블럭이 유효한 위치에 없다면 게임 종료
        if((0 > x || x >= COL) || (0 > y)){
            available = FALSE;
            fprintf(stderr, "Game Over!\nInvalid binding(2)\n");
            exit(EXIT_FAILURE);
        }
    }
    if(available){
        for(int i = 0; i < 4; i++){
            int x = block->position[i][0] + base_x;
            int y = block->position[i][1] + base_y;
            
            if(y < ROW){    // y가 6보다 큰 블럭 위치는 무시
                map_arr[y][x] = 1;
            }
        }
    }
}

void unbind_block(){
    int (*map_arr)[COL] = map->map;
    Block* block = map->current_block;
    int base_x = block->x, base_y = block->y;

    for(int i = 0; i < 4; i++){
        int x = block->position[i][0] + base_x;
        int y = block->position[i][1] + base_y;

        // 유효 범위 내 값만 0으로, OutofIndex Error 방지
        if((0 <= x && x < COL) && (0 <= y && y < ROW)){
            map_arr[y][x] = 0;
        }
    }
}

void floor_rise(){
    int (*map_arr)[COL] = map->map;
    int* floor = map->floor;
    Block* block = map->current_block;
    int base_x = block->x, base_y = block->y;

    for(int i = 0; i < 4; i++){
        int x = block->position[i][0] + base_x;
        int y = block->position[i][1] + base_y;

        // 바닥은 블럭의 높이보다 1 높은 값이나 현재 바닥 높이 중 큰 값을 선택
        floor[x] = max(floor[x], y + 1);
    }
}

void check_erasable(){
    int (*map_arr)[COL] = map->map;
    int* floor = map->floor;
    int* erasable = map->erasable;

    // 현재 행에 대해 모든 열이 1이면 지울 수 있는 상태; 높은 행부터 확인
    for(int i = 0; i < ROW; i++){
        boolean flag = TRUE;
        for(int j = 0; j < COL; j++){
            if(map_arr[i][j] == 0){
                flag = FALSE;
                break;
            }
        }
        if(flag){
            erasable[map->erasable_count++] = i;
        }
    }
}

void erase(){
    int (*map_arr)[COL] = map->map;
    int* floor = map->floor;
    int* erasable = map->erasable;

    if(map->erasable_count == 0){
        printf("Nothing to erase!\n");
    }

    for(int i = map->erasable_count - 1; i >= 0; i--){
        int erase_row = erasable[i];
        // erase rows
        if(erase_row == ROW - 1){
            for(int j = 0; j < COL; j++)
                map_arr[erase_row][j] = 0;
        }
        else{
            for(int j = erase_row; j < ROW - 1; j++){
                for(int k = 0; k < COL; k++){
                    map_arr[j][k] = map_arr[j + 1][k];
                }
            }
        }

        // update the floor 
        for(int j = 0; j < COL; j++){
            int max_y = 0;
            for(int k = ROW - 2; k >= 0; k--){
                if(map_arr[k][j] == 1){
                    max_y = max(max_y, k + 1);
                    break;
                }
            }
            floor[j] = max_y;
        }
    }

    // Compute score & Add
    int basic_score = 5 * (map->erasable_count * (map->erasable_count + 1));
    int combo_score = basic_score * map->combo;
    map->score += basic_score + combo_score;

    // Update Combo
    if(0 < map->erasable_count){
	if(map->erased_before){
		if(map->erasable_count < 3)
			map->combo += map->erasable_count + 1;
		else if(map->erasable_count >= 3)
			map->combo += 2 * map->erasable_count;
	}
	else{
		if(1 < map->erasable_count && map->erasable_count <= 3)
			map->combo += map->erasable_count - 1;
		else if(map->erasable_count > 3)
			map->combo += 2 * map->erasable_count;
	}
        map->erased_before = TRUE;
        map->combo = min(map->combo, 8);            
    }
    else{
        map->erased_before = FALSE;
        map->combo--;
	map->combo = max(map->combo, 0);
    }
    map->erasable_count = 0;
}

Map* get_map(){
    return map;
}

boolean can_floor_rise(){
    int (*map_arr)[COL] = map->map;
    int* floor = map->floor;
    Block* block = map->current_block;
    int base_x = block->x, base_y = block->y;

    for(int i = 0; i < 4; i++){
        int x = block->position[i][0] + base_x;
        int y = block->position[i][1] + base_y;

        // 최대 높이에 이미 도달했거나 바닥이 블럭 높이보다 높은경우
        if(floor[x] > y || floor[x] >= 6){
            return FALSE;
        }
    }
    return TRUE;
}
