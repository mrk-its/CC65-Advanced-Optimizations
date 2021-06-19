#ifndef ATARI_H
#define ATARI_H

struct T_OS {
  unsigned char *savmsc;
};

#define OS (*((struct T_OS *)0x58))

#endif

