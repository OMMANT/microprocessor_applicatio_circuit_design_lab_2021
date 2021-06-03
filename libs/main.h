#ifndef MAIN_H
#define MAIN_H
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

#include "ieb.h"
#include "dot.h"

typedef enum {
	FALSE = 0,
	TRUE  = 1
} truth_t;

clock_t start_time;

void init();
short* mapper(off_t offset);
void unmapper();
void emergency_closer();

#endif