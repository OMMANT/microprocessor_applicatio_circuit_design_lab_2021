#ifndef MAP_H
#define MAP_H
#define ROW 7
#define COL 5
#define N_BLOCK 5

#include "utils.h"
#include "block.h"

/* ABSTRACT DATA TYPE DEFINITION */
typedef struct MAP{
    int map[ROW][COL];      // 실제 (7X5) 크기의 맵
    int floor[COL];         // 각 열의 바닥 (가장 높은 층)
    int erasable[ROW];      // 삭제 가능한 행을 저장해두는 리스트
    int erasable_count, score, combo;   // erasable 리스트의 크기, 점수, 콤보 변수
    boolean erased_before;              // 이전 블럭에 지운 기록이 있는지 저장

    Block* current_block;               // 현재 떨어지고 있는 블럭
    Type next_block_type;               // 후에 떨어질 블럭
}Map;

/* ABSTRACT FUNCTION DEFINITION */
void map_init();    // 맵을 초기화하는 함수; 전역 변수 map에 메모리를 할당하고 값을 초기화
void map_print();   // 맵의 상태를 콘솔로 출력하는 함수; dot matrix, led에 값을 쓰기도 한다
void bind_block();  // 현재 떨어지고 있는 블럭의 위치와 맵을 연결시켜주는 함수; 떨어지는 블럭은 맵에 고정되는것이 아님
void unbind_block();    // bind_block으로 블럭의 위치와 맵이 연결된 것을 해제하는 함수; 
void floor_rise();      // map->floor을 조절해주는 함수; 블럭이 바닥에 닿았을 때 바닥을 올려주는 역할을 함
void check_erasable();  // 지울 수 있는 행이 있는지 확인하는 함수
void erase();           // 지울 수 있는 행을 지우는 함수
Map* get_map();         // 전역변수인 map을 직접 참조하지 않도록 map을 반환
boolean can_floor_rise();   // map->floor의 값을 조절할 수 있는지 확인하는 함수; 게임 종료 조건

/* GLOBAL VARIABLE */
Map* map;

#endif
