#include "dot.h"

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
    usleep(1000);
}

void dot_write(int (*dot_mat)[MAX_DOT]){
    for(int i = 0; i < MAX_DOT; i++){
        short temp = 0;
        for(int j = 6; j >= 0; j--){
            temp <<= 1;
            temp += (short)dot_mat[j][i];
            *dot[i] = temp;
        }
    }
    usleep(30000);
}