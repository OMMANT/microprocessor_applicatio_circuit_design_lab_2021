#include "main.h"
#include "map.h"
#include "queue.h"

int main(int argc, char *argv[]){
    init_variable();
    map_print();

    // for(int i = 0; i < 5; i++){
    //     printf("i: %d\n", i);
    //     for(int j = 0; j < 2; j++){
    //         for(int k = 0; k < 4; k++){
    //             printf("%d ", hello[j][k][i]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }

    // while(1){
    //     if(kbhit()){
    //         char ch = getch();

    //         if(ch == KEYPAD_COUNT_CLOCK){

    //         }
    //         else if(ch == KEYPAD_CLOCK){

    //         }
    //         else if(ch == KEYPAD_FALL){
                
    //         }
    //     }
    // }
    int i = 0;
    while(1){
        clock_t c_time = clock(), b_time = clock();

        if(c_time - start_time >= 3 * CLOCKS_PER_SEC){
            system("clear");
            map_block_down();            
            map_refresh();
            map_print();
            printf("%d Sec\n", 2 * ++i);
            start_time = c_time;
        }
        if(i > 10)
            break;
    }

    return 0;   
}

void init_variable(){
    start_time = clock();
    srand(time(NULL));    
    map_init();
}