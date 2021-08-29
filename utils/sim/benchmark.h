#include <stdio.h>
#include <stdlib.h>

#define SAVMSC ((unsigned char *)0x8000)

void start_benchmark(void)
{
    reset_clock();
}


void end_benchmark(void)
{
    unsigned long ticks = clock();
    printf("ticks: %lu\n", ticks);
}
