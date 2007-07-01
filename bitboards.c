#include "bitboards.h"
#include "bitboard.h"

void init_pos_bitboards();
void init_inverse_bitboards();

static int initted;

void bitboards_init(){
  if (initted)
    return;
  initted = 1;
  init_pos_bitboards();
  init_inverse_bitboards();
}

void init_pos_bitboards(){
  int row, col;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      setEmptyBitboard(&pos[row][col]);
      setFilled(&pos[row][col], row, col);
      //printBitboard(&pos[row][col]);
    }
  }
}

void init_inverse_bitboards(){
  int row, col;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      inverse[row][col] = pos[row][col];
      invertBitboard(&inverse[row][col]);
      //printBitboard(&inverse[row][col]);
    }
  }
}
