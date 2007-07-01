#include "bitboard.h"

int main(){
  bitboard bb;
  int row, col;

  setEmptyBitboard(&bb);

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      if (row < col){
	setFilled(&bb, row, col);
      }
    }
  }

  printf("***UPPER RIGHT\n");
  printBitboard(&bb);
  printf("\n%llx\n\n", bb);

  setFullBitboard(&bb);

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      if (row < col){
	setEmpty(&bb, row, col);
      }
    }
  }

  printf("***LOWER LEFT\n");
  printBitboard(&bb);
  printf("\n%llx\n\n", bb);

  setEmptyBitboard(&bb);

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      if (row < (8 - col)){
	setFilled(&bb, row, col);
      }
    }
  }

  printf("***UPPER LEFT\n");
  printBitboard(&bb);
  printf("\n%llx\n\n", bb);

  printf("***LOWER RIGHT\n");
  bb = ~bb;
  printBitboard(&bb);
  printf("\n%llx\n\n", bb);
  
}
