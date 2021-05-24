#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "map.h"

int main(int argc, char* argv[]){
    init();
    int arr[4][2] = {{0, 0}, {1, 0}, {-1, 0}, {2, 0}};
    int arr2[4][2] = {{0, 0}, {1, 0}, {-1, 0}, {1, 1}};
    Type type = straight;
    Block* test = get_block(type);

    printf("Hello, World!\n");

    for(int i = 0; i < 4; i++){
        printf("(%d, %d)\n", test->position[i][0], test->position[i][1]);
    }

    return 0;
}

void init(){
    srand(time(NULL));
    start_time = clock();
    block_init();
    map_init();
}