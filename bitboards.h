#ifndef BITBOARDS_H
#define BITBOARDS_H

#define UPPER_RIGHT 0x80c0e0f0f8fcfell
#define LOWER_LEFT 0xff7f3f1f0f070301ll
#define UPPER_LEFT 0x103070f1f3f7fffll
#define LOWER_RIGHT 0xfefcf8f0e0c08000ll

#include "bitboard.h"

/* This array of bitboards has a 1 set in the specified [row][col]
   coordinate */
bitboard pos[8][8];
/* The inverse bitboards of above, i.e. ones everywhere except
   [row][col] */
bitboard inverse[8][8];

void bitboards_init();

#endif
