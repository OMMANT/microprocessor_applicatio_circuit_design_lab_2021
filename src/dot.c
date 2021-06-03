#include "dot.h"

static unsigned short dot_decimal[10][MAX_DOT] = {
    {0x7f, }
};

static short* dot[MAX_DOT];

void init_dot(short * address[]){
    for(int i = 0; i < MAX_DOT; i++){
        dot[i] = address[i];
    }
}

void dot_clear(){
    for(int i = 0; i < MAX_DOT; i++){
        *dot[i] = 0;
    }
    usleep(0);
}

void dot_write(int (*dot_mat)[MAX_DOT]){
    for(int i = 0; i < MAX_DOT; i++){
        int temp = 0;
        for(int j = 6; j >= 0; j--){
            temp <<= 1;
            temp += dot_mat[j][i];
            *dot[i] = temp;
        }
    }
}