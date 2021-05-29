#include "utils.h"

void copy(int* src, int* dst, int N){
    for(int i = 0; i < N; i++)
        dst[i] = src[i];
}

int min(int a, int b){
    if (a < b) return a;
    else return b;
}

int max(int a, int b){
    if (a > b) return a;
    else return b;
}