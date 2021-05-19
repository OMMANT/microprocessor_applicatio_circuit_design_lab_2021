#ifndef QUEUE
#define QUEUE
#include "utils.h"

typedef struct QUEUE{
    int front, rear;
    int max_n;
    int* data;
}Queue;

Queue* create_queue(int n);
Queue* enqueue(Queue* queue, int e);
int dequeue(Queue* queue);
boolean is_empty(Queue* queue);
boolean is_full(Queue* queue);

#endif