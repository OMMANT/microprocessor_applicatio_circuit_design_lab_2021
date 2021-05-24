#include "main.h"
#include "map.h"

int main(int argc, char* argv[]){
    int time = 0;
    clock_t b_time = clock();

    init_variable();

    while(TRUE){
        clock_t c_time = clock();
        
        if(c_time - b_time >= CLOCKS_PER_SEC){
            // system("clear");
            int rotate = rand() % 3;
            if(rotate){
                if(rotate == 1)
                    block_rotate_left();
                else
                    block_rotate_right();
            }
            map_block_down();
            int r = rand() % 3;
            if(r == 0)
                block_move_left();
            else if(r == 1)
                block_move_right();

            map_refresh();
            map_print();
            printf("%d Sec\n", ++time);
            b_time = c_time;
        }
        if(time > 20)
            break;
    }

    return 0;
}

void init_variable(){
    start_time = clock();
    srand(time(NULL));
    map_init();
}