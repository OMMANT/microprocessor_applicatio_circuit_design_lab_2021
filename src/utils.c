#include "utils.h"

void copy(int* src, int* dst, int N){
    // src의 원소를 dst에 복사시키는 함수
    for(int i = 0; i < N; i++)
        dst[i] = src[i];
}

int min(int a, int b){
    // a 와 b 중 작은 것을 반환
    if (a < b) return a;
    else return b;
}

int max(int a, int b){
    // a와 b 중 큰 것을 반환
    if (a > b) return a;
    else return b;
}