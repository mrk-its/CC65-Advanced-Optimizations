#include <atari.h>

#define READ_BYTE(addr) *(volatile unsigned char *)addr
#define WRITE_BYTE(addr, value) *((volatile unsigned char *)addr) = value

#define SAVMSC OS.savmsc

void start_benchmark(void)
{
        unsigned char t = READ_BYTE(0x14);
        while(READ_BYTE(0x14)==t);
        WRITE_BYTE(0x14, 0);
        WRITE_BYTE(0x13, 0);
}

void end_benchmark(void)
{
	unsigned int ticks = READ_BYTE(0x14) | (unsigned int)READ_BYTE(0x13) << 8;
	OS.savmsc[0] = 0x10 + (ticks / 100) % 10;
	OS.savmsc[1] = 0x10 + (ticks / 10) % 10;
	OS.savmsc[2] = 0x10 + ticks % 10;
        for(;;);
}
