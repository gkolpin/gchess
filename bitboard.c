#include "position.h"
#include "bitboards.h"
#include "bitboard.h"
#include <stdio.h>

void initPositions();
int getPositionOfFilledInRow(r_data);

void bb_init(){
  bitboards_init();
  initPositions();
}

position positions[8][256];

/* Initializes table of bitboards and positions that
   are filled */
void initPositions(){
  int row, i_row_descr;
  r_data row_descr;
  
  for (row = 0; row < 8; row++){
    for (i_row_descr = 0, row_descr = 0; i_row_descr < 256; row_descr++, 
	   i_row_descr++){
      P_SET_ROW(&positions[row][row_descr], row);
      P_SET_COL(&positions[row][row_descr], getPositionOfFilledInRow(row_descr));
    }
  }
}

int getPositionOfFilledInRow(r_data row_descr){
  int pos = 0;
  while (row_descr >>= 1) pos++;
  return pos;
}

void setEmptyBitboard(bitboard* bb){
  *bb = (bitboard)0;
}

void setFullBitboard(bitboard* bb){
  *bb = (bitboard)~0;
}

void invertBitboard(bitboard* bb){
  *bb = ~*bb;
}

void setFilled(bitboard* bb, int row, int col){
  *bb |= ((bitboard)1 << (row * 8 + col));
  //  *bb |= (1 << ((8 - row) * 8 + col));
}

void setFilledFast(bitboard* bb, int row, int col){
  *bb |= pos[row][col];
}

void setEmpty(bitboard* bb, int row, int col){
  bitboard b = ~0;

  b ^= ((bitboard)1 << (row * 8 + col));

  *bb &= b;
  //  *bb |= (1 << ((8 - row) * 8 + col));
}

void setEmptyFast(bitboard* bb, int row, int col){
  *bb &= inverse[row][col];
}

void fillRow(bitboard *bb, int row){
  ((r_data*)(bb))[row] = (r_data)255;
}

void fillRowWith(bitboard *bb, int row, r_data c){
  ((r_data*)(bb))[row] = c;
}

void fillAllRowsWith(bitboard *bb, r_data c){
  int row;
  for (row = 0; row < 8; row++){
    ((r_data*)(bb))[row] = c;
  }
}

r_data getRow(bitboard *bb, int row){
  return ((r_data*)(bb))[row];
}

void setRow(bitboard *bb, int row, r_data rowData){
  fillRowWith(bb, row, rowData);
}

r_data getCol(bitboard *bb, int col){
  int row;
  r_data returnval = 0;
  
  for (row = 0; row < 8; row++){
    if (isFilledFast(bb, row, col))
      returnval |= (r_data)((r_data)1 << (7 - row));
  }

  return returnval;
}

void union_bb(bitboard *bb1, bitboard *bb2, bitboard *result_bb){
  *result_bb = *bb1 | *bb2;
}

void union_bbSet(bitboard *bb, int numBB, bitboard *result){
  int i;
  setEmptyBitboard(result);

  for (i = 0; i < numBB; i++){
    union_bb(&bb[i], result, result);
  }
}

void intersect_bb(bitboard *bb1, bitboard *bb2, bitboard *result){
  *result = *bb1 & *bb2;
}

void xor_bb(bitboard *bb1, bitboard *bb2, bitboard *result){
  *result = *bb1 ^ *bb2;
}

void flipboard(bitboard *bb){
  r_data *c_array = (r_data*)bb;
  int i;
  int j;
  r_data t;
  for (i = 0, j = 7; i < 4; i++, j--){
    t = c_array[i];
    c_array[i] = c_array[j];
    c_array[j] = t;
  }
}

void rotateBoard90(bitboard *bb){
  int row, col;
  bitboard temp;

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      if (isFilled(bb, row, col))
	setFilled(&temp, 7 - col, row);
      else
	setEmpty(&temp, 7 - col, row);
    }
  }
  
  *bb = temp;
}

void rotateBoardNeg90(bitboard *bb){
  int row, col;
  bitboard temp;

  /* col becomes row, and 7 - row becomes col */

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      if (isFilled(bb, row, col))
	setFilled(&temp, col, 7 - row);
      else
	setEmpty(&temp, col, 7 - row);
    }
  }

  *bb = temp;
}

/* 45 degree rotations make sloping lines turn into rows */

void rotateBoardNeg45(bitboard *bb){
  /* We will rotate by -45 degrees - 
     First column stays the same, but each other column
     is shifted up by a certain amount (the column number
     counting from the left) */

  int i;
  r_data row;
  int shift_amount;
  r_data temp_row;

  /* We will be shifting columns, so first rotate by 90 so 
     that the columns become rows and we can use bitwise operators */

  rotateBoard90(bb);

  /* Iterate row by row (last row stays the same) */
  for (i = 0, shift_amount = 7; i < 7; i++, shift_amount--){
    /* Get the current row */
    row = temp_row = getRow(bb, i);
    
    /* bit shift right temp_row by (8 - shift_amount) */
    temp_row >>= 8 - shift_amount;

    /* bit shift left row by shift_amount  */
    row <<= shift_amount;

    /* Now bitwise OR the two together */
    row = row | temp_row;

    /* Now set the row in the bitboard */
    setRow(bb, i, row);
  }

  /* Finally, flip the board -90 degrees */
  rotateBoardNeg90(bb);
}

void rotateBoard45(bitboard *bb){

  /* We'll take advantage of the rotateBoardNeg45 procedure -
     We'll flip the board, rotate by -45, and flip the board back. */

  flipboard(bb);
  rotateBoardNeg45(bb);
  flipboard(bb);
}

int isFilled(bitboard *bb, int row, int col){
  return (*bb & ((bitboard)1 << (row * 8 + col))) != 0;
}

int isFilledFast(bitboard *bb, int row, int col){
  return *bb & pos[row][col] ? 1 : 0;
}

int getIndexOfFilled(bitboard *bb, int numBB, int row, int col){
  bitboard mask = 0;
  int i;

  setFilledFast(&mask, row, col);

  for (i = 0; i < numBB; i++){
    if ((bitboard)(mask & bb[i]) != (bitboard)0)
      return i;
  }
  
  return -1;
}

position * getPositionOfFilled(bitboard* bb){
  unsigned int firstPos, secondPos;
  firstPos = (*bb >> 32) == 0 ? 0 : 1;
  secondPos = ((unsigned short*)&
	       ((unsigned int*)bb)[firstPos])[1] == 0 ? 0 : 1;
  firstPos = ((((unsigned char*)&
		((unsigned short*)&
		 ((unsigned int*)bb)[firstPos])[secondPos])[1] == 0) ? 
	      0 : 1) + firstPos * 4 + secondPos * 2;
  return &positions[firstPos][getRow(bb, firstPos)];
}

void printBitboard(bitboard* bb){
  int i;
  for (i = 0; i < 64; i++){
    if (i % 8 == 0)
      printf("\n");
    if (*bb & ((bitboard)1 << i))
      printf("%d ", 1);
    else 
      printf("%d ", 0);
  }
  printf("\n");
}
