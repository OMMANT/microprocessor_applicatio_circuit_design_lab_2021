#ifndef DOT_H
#define DOT_H

#include <unistd.h>
#define MAX_DOT 5

void init_dot(short *address[]);
void dot_clear();
void dot_write(int (*dot_mat)[MAX_DOT]);

#endif