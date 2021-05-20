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
            map_block_down();
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