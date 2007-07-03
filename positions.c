#include "positions.h"
#include "types.h"
#include "position_list.h"

void positions_init(){
  int row, col;
  r_data rdRow;
  bitboard bbTemp = 0;
  position pTemp;
  for (row = 0; row < 8; row++){
    for (rdRow = 0; 1; rdRow++){
      fillRowWith(&bbTemp, 0, rdRow);
      for (col = 0; col < 8; col++){
	
	if (isFilled(&bbTemp, 0, col)){
	  P_SET_ROW(&pTemp, row);
	  P_SET_COL(&pTemp, col);
	  pl_addPos(&position_lists[row][rdRow], &pTemp);
	}

      }
      if (rdRow == 255){
	break;
      }
    }
  }
}
