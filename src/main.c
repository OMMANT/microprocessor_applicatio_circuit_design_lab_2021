#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "map.h"
#include "led.h"

static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5
};

static int fd;
static int map_counter = 0;
static void * map_data[100];
short *led, *dot[MAX_DOT];

int main(int argc, char* argv[]){
    init();
    Map* map = get_map();
    while(TRUE){
	clock_t c_time = clock();
	unbind_block();
	char c = '\0';
	c = getchar();
	if(c == '\n')
	    continue;
	if(c == 'q'){
	    rotate_left(map->current_block);
	    bind_block();
	}
	else if(c == 'e'){
	    rotate_right(map->current_block);
	    bind_block();
	}
	else if(c == 'a'){
	    move_left(map->current_block);
	    bind_block();
	}
	else if(c == 'd'){
	    move_right(map->current_block);
	    bind_block();
	}
	else if(c == 's'){
	    block_descent(map->current_block, map->floor);
	    bind_block();
	}
	else{
	    if(can_move_down()){
		move_down(map->current_block);
	    }
	    else{
		if(can_floor_rise()){
		    floor_rise();
		    stuck_map(map->current_block);
		    check_erasable();
		    erase();
		}
		else{
		    printf("Gave Over!\n");
		    exit(0);
		}
	    }
	    bind_block();
	}
	printf("c: %c\n", c);
	map_print();
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
    init_led(led);
    init_dot(dot);
    dot_clear();
    srand(time(NULL));
    start_time = clock();
    block_init();
    map_init();

}


short * mapper(off_t offset) {
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

truth_t inputter() {
    unbind_block();
	char c = '\0';

	printf("\n");
	printf("**********************************************\n");
	printf("*     Please type a number (q e a d s p)    *\n");
	printf("*  q : rotate left      r   : rotate right  *\n");
	printf("*  a : move left        d : move right      *\n");
    printf("*         s : move down directly            *\n");
	printf("*     p : terminate the program             *\n");
	printf("**********************************************\n\n");

	c = getchar();
	printf("Bind conditaion\n");
	int base_x = map->current_block->x, base_y = map->current_block->y;
	for(int i = 0; i < 4; i++){
		int x = base_x + map->current_block->position[i][0];
		int y = base_y + map->current_block->position[i][1];
		
		printf("(%d, %d)\t", x, y);
	}
	printf("\nMap Status\n");
	for(int i = ROW - 1; i >= 0; i--){
		printf("| ");
		for(int j = 0; j < COL; j++){
			if(map->map[i][j] == 1)
				printf("* ");
			else printf("  ");
		}
		printf("|\n");
	}
	printf("\n");
	if(c == '\n')
        inputter();
    if(c == 'p')
        return FALSE;
    if(c == 'q'){
        rotate_left(map->current_block);
    }
	else if(c == 'e') {
		rotate_right(map->current_block);
	}
	else if(c == 'a'){
        move_left(map->current_block);
    }
    else if(c == 'd'){
        move_right(map->current_block);
    }
    else if(c == 's'){
        block_descent(map->current_block, map->floor);
    }
    else{
	printf("working\n");
        if(can_move_down()){
            move_down(map->current_block);
        }
        else{
            if(can_floor_rise()){
                floor_rise();
                stuck_map(map->current_block);
                check_erasable();
                erase();
            }
            else{
                printf("Game Over!\n");
                return FALSE;
            }
        }
    }
    bind_block();
    map_print();
	
	return TRUE;
}
