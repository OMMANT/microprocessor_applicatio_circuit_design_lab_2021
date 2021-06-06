#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "map.h"
#include "led.h"
#include "fnd.h"
#include "clcd.h"

static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5
};
static off_t IEB_FND[MAX_FND] = {
	IEB_FND0,
	IEB_FND1,
	IEB_FND2,
	IEB_FND3,
	IEB_FND4,
	IEB_FND5,
	IEB_FND6,
	IEB_FND7
};

static int fd;
static int map_counter = 0;
static void * map_data[100];
short *led, *dot[MAX_DOT], *fnd[MAX_FND], *clcd_data, *clcd_cmd;

int main(int argc, char* argv[]){
    init();		// 변수 초기화
    Map* map = get_map(); // 초기화된 전역 변수(map)을 가져와 지역 변수에 저장
    while(TRUE){		
		printf("\n");
		printf("**********************************************\n");
		printf("*     Please type a number (q e a d s p)     *\n");
		printf("*  q : rotate left      e   : rotate right   *\n");
		printf("*    a : move left        d : move right     *\n");
		printf("*         s : move down directly             *\n");
		printf("*        p : terminate the program           *\n");
		printf("*         others : move down 1 block         *\n");
		printf("**********************************************\n\n");
		clock_t c_time = clock();
		unbind_block();  // bind_block으로 블럭의 위치와 맵이 연결된 것을 해제하는 함수; 
		char c = '\0';
		c = getchar();	// keypad 입력을 받을 수 없어 getchar()로 입력값을 받음
		if(c == '\n')
			continue;
		if(c == 'q'){
			rotate_left(map->current_block); 	// 블럭을 왼쪽으로 90도 회전시키는 함수
		}
		else if(c == 'e'){
			rotate_right(map->current_block);	// 블럭을 오른쪽으로 90도 회전시키는 함수
		}
		else if(c == 'a'){
			move_left(map->current_block);		// 블럭을 왼쪽으로 옮기는 함수
		}
		else if(c == 'd'){
			move_right(map->current_block);		// 블럭을 오른쪽으로 옮기는 함수
		}
		else if(c == 's'){
			block_descent(map->current_block, map->floor);	// 블럭을 최대한 아래로 옮기는 함수
		}
		else if(c == 'p'){
			printf("TETROMINO TERMINATE!\nInput (p)\n");	// p 입력시 프로그램 종료
			exit(EXIT_SUCCESS);
		}
		else{
			if(can_move_down()){
				move_down(map->current_block);			// 블럭을 아래로 한 칸 옮기는 함수
			}
			else{
				if(can_floor_rise()){
					floor_rise();						// map->floor을 조절해주는 함수; 블럭이 바닥에 닿았을 때 바닥을 올려주는 역할을 함
					stuck_map(map->current_block);		// 블럭이 바닥에 닿은 이후 블럭을 맵에 고정시키고 다음 블럭으로 넘어가는 함수
					check_erasable();
					erase();    	// 지울 수 있는 행이 있는지 확인 후 행을 지우기
				}
				else{
					printf("Gave Over!\n");
					exit(0);
				}
	    	}
		}
		bind_block();	// 현재 떨어지고 있는 블럭의 위치와 맵을 연결시켜주는 함수; 떨어지는 블럭은 맵에 고정되는것이 아님
		map_print();	// 맵의 상태를 콘솔로 출력하는 함수; dot matrix, led에 값을 쓰기도 한다
    }
    unmapper();
    close(fd);

    return 0;
}

void init(){
    fd = open("/dev/mem", O_RDWR|O_SYNC);
    if (fd == -1){
        fprintf(stderr, "Cannot open /dev/mem file");
        exit(EXIT_FAILURE);
    }

    led = mapper(IEB_LED);
    for(int i = 0; i < MAX_DOT; i++){
        dot[i] = mapper(IEB_DOT[i]);
    }
	for(int i = 0; i < MAX_FND; i++){
        fnd[i] = mapper(IEB_FND[i]);
    }

	clcd_cmd =  mapper(IEB_CLCD_CMD);
	clcd_data =  mapper(IEB_CLCD_DATA);


    init_led(led);
    init_dot(dot);
	init_fnd(fnd);
	init_clcd(clcd_cmd, clcd_data);
    dot_clear();
	fnd_decimal_number(0);
	clcd_make_board();
	clcd_update(0, 0);
    srand(time(NULL));
    start_time = clock();
    block_init();
    map_init();

}

short *mapper(off_t offset) {
	map_data[map_counter] = mmap(NULL, sizeof(short), PROT_WRITE, MAP_SHARED, fd, offset);
	if ( map_data[map_counter] == MAP_FAILED ) {
		fprintf(stderr, "Cannot do mmap()");
		emergency_closer();
	}
	return (short *)map_data[map_counter++];
}

void unmapper() {
	int i;
	for( i=0; i<map_counter; i++) {
		munmap(map_data[i], sizeof(short));
	}
	map_counter = 0;
}

void emergency_closer() {
	unmapper();
	close(fd);
	exit(EXIT_FAILURE);
}
