#ifndef BLOCK_H
#define BLOCK_H
#include "utils.h"

/* GLOBAL VARIABLE */
// 좌표는 각각 (x, y) 4개의 점으로 구성
static const int SQUARE_BLOCK[4][2] = {
    {0, 0}, {1, 0}, {0, 1}, {1, 1}
};
static const int CROSS_BLOCK[4][2] = {
    {0, 0}, {1, 0}, {-1, 0}, {0, 1}
};
static const int J_BLOCK[4][2] = {
    {0, 0}, {1, 0}, {-1, 0}, {-1, 1}
};
static const int L_BLOCK[4][2] = {
    {0, 0}, {1, 0}, {-1, 0}, {1, 1}
};
static const int STRAIGHT_BLOCK[4][2] = {
    {0, 0}, {1, 0}, {-1, 0}, {2, 0}
};

int* blocks[5];
/* blocks 참조 방법 
 * blocks[0~4] = 네모, 십자, J, L, 직선
 * blocks[type][2 * i + 0] i번 째 x 좌표
 * blocks[type][2 * i + 1] i번 째 y 좌표
 */

/* ABSTRACT DATA TYPE DEFINITION */
typedef struct BLOCK{
    int position[4][2];
    int x, y;
}Block;

typedef enum BLOCK_TYPE{
    square,
    cross,
    j,
    l,
    straight
}Type;

/* ABSTRACT FUNCTION DEFINITION */
void block_init();  // 블럭의 기본 초기화 함수
Block* get_block(int type); // 초기화된 블럭 반환
void stuck_map(Block* b);       // 블럭이 바닥에 닿은 이후 블럭을 맵에 고정시키고 다음 블럭으로 넘어가는 함수
void move_left(Block* b);       // 블럭을 왼쪽으로 옮기는 함수
void move_right(Block* b);      // 블럭을 오른쪽으로 옮기는 함수
void move_down(Block* b);       // 블럭을 아래로 한 칸 옮기는 함수
void block_descent(Block* b, int* floor);   // 블럭을 최대한 아래로 옮기는 함수
boolean can_move_down();        // 블럭을 아래로 한 칸 움직일 수 있는지 확인하는 함수
void rotate_left(Block* b);     // 블럭을 왼쪽으로 90도 회전시키는 함수
void rotate_right(Block* b);    // 블럭을 오른쪽으로 90도 회전시키는 함수
void check_validation(Block* b);    //블럭의 위치 유효성을 확인하고 조정하는 함수
#endif
