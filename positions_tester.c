#include <stdio.h>

#include "positions.h"
#include "bitboard.h"
#include "types.h"
#include "position_list.h"

void testPositions(){
  int row;
  r_data rowDescr;
  bitboard bb = 0;

  for (row = 0; row < 8; row++){
    for (rowDescr = 0; 1; rowDescr++){
      bb = 0;
      fillRowWith(&bb, row, rowDescr);

      printBitboard(&bb);
      printf("\n");
      pl_print(&position_lists[row][rowDescr]);

      if (rowDescr == 255){
	break;
      }
    }
  }
}

int main(){
  positions_init();
  testPositions();
  return 0;
}
