#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "map.h"

int main(int argc, char* argv[]){
    int mode = 0;
    init();
    map_print();
    Map* map = get_map();
    while(1){
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
        else if(c == 'r'){
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
            ;
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
                    printf("erasable: [ ");
                    for(int i = 0; i < map->erasable_count; i++){
                        printf("%d ", map->erasable[i]);
                    }
                    printf("]\n");
                    erase();
                }
                else{
                    printf("Game Over!\n");
                    exit(1);
                }
            }
            bind_block();
        }
        printf("c: %c\n", c);
        map_print();

        // while (c_time - start_time < CLOCKS_PER_SEC){
        //     c_time = clock();
        // }
        // start_time = c_time;
    }

    return 0;
}

void init(){
    srand(time(NULL));
    start_time = clock();
    block_init();
    map_init();
}