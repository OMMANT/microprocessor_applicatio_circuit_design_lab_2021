#include "queue.h"
#include <stdlib.h>

Queue* create_queue(int n){
    Queue* ptr = (Queue*)malloc(sizeof(Queue));

    ptr->front = 0;
    ptr->rear = 0;
    ptr->max_n = n;
    ptr->data = (int*)malloc(sizeof(int) * (n + 1));
}

boolean is_empty(Queue* queue){
    if(queue->front == queue->rear)
        return TRUE;
    else return FALSE;
} 

boolean is_full(Queue* queue){
    if(queue->front - queue->rear == 1 || queue->rear - queue->front == queue->max_n)
        return TRUE;
    else return FALSE;
}

Queue* enqueue(Queue* queue, int e){
    if(!is_full(queue))
        queue->data[(queue->rear)++] = e;
    
    if(!(0 <= queue->rear && queue->rear < queue->max_n + 1))
        queue->rear = 0;
    
    return queue;
}

int dequeue(Queue* queue){
    int datum = -1;

    if(!is_empty(queue))
        datum = queue->data[(queue->front)++];

    if(!(0 <= queue->front && queue->front < queue->max_n + 1))
        queue->front = 0;

    return datum;
}