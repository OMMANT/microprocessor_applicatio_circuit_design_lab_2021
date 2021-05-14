#include "main.h"
#include "keypad.h"

int main(int argc, char *argv[]){
    init_variable();

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
    while(1){
        clock_t c_time = clock(), b_time = clock();

        if(c_time - start_time >= 20 * CLOCKS_PER_SEC)
            break;

    }

    return 0;   
}

void init_variable(){
    start_time = clock();
    srand(time(NULL));
    init_DM();
}