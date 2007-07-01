#include "bitboard.h"
#include "bitboards.h"
#include <stdio.h>

void bbt_init(){
  bb_init();
}

int testGetIndexOfFilled(){

  bitboard *bb = (bitboard*)malloc(sizeof(bitboard) * 4);
  int i;

  for (i = 0; i < 4; i++){
    setEmptyBitboard(&bb[i]);
    setFilled(&bb[i], i, 0);
  }
  
  if (getIndexOfFilled(bb, 4, 2, 0) != 2){
    printf("%d\n", getIndexOfFilled(bb, 4, 2, 0));
    return 0;
  }
  
  return 1;

}

void testFlippedBitboard(){
  bitboard bb;
  
  printf("\nTESTING FLIPPED BITBOARD\n");

  setEmptyBitboard(&bb);
  
  setFilled(&bb, 6, 5);

  flipboard(&bb);

  printBitboard(&bb);
}

void testRotatedBitboard(){
  bitboard bb;
  printf("\nTESTING ROTATED BITBOARD\n");
  
  setEmptyBitboard(&bb);
  
  setFilled(&bb, 6, 5);

  printBitboard(&bb);

  rotateBoard90(&bb);

  printBitboard(&bb);

  rotateBoardNeg90(&bb);

  printBitboard(&bb);

  printf("\nTESTING ROTATED 45 BITBOARD\n");

  setEmptyBitboard(&bb);

  int row, col;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      if ((row + col) % 2 == 0){
	setFilled(&bb, row, col);
      }
    }
  }

  printBitboard(&bb);

  rotateBoard45(&bb);

  printBitboard(&bb);

  setEmptyBitboard(&bb);

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      if ((row + col) % 2 == 1){
	setFilled(&bb, row, col);
      }
    }
  }

  printBitboard(&bb);
  
  rotateBoardNeg45(&bb);
  
  printBitboard(&bb);

  setEmptyBitboard(&bb);

  setFilled(&bb, 7, 7);

  printBitboard(&bb);
  
  rotateBoard45(&bb);
  
  printBitboard(&bb);

  setEmptyBitboard(&bb);

  setFilled(&bb, 7, 7);

  rotateBoardNeg45(&bb);

  printBitboard(&bb);

  bitboard ur = UPPER_RIGHT;

  printBitboard(&ur);

  rotateBoard45(&ur);
  printBitboard(&ur);
  rotateBoardNeg45(&ur);

  printBitboard(&ur);

}

void testGetCol(){
  bitboard bb;
  printf("\nTESTING GETCOL\n");

  setEmptyBitboard(&bb);

  setFilled(&bb, 6, 5);
  setFilled(&bb, 2, 5);
  setFilled(&bb, 0, 5);
  
  int i;
  for (i = 0; i < 8; i++){
    if (isFilled(&bb, i, 5)){
      printf("%d, %d is filled\n", i, 5);
    }
  }

  printf("\n");

  printBitboard(&bb);

  printf("\ncol descr: %hhu\n", getCol(&bb, 5));
  printf("\ncol descr: %hhu\n", getCol(&bb, 6));
  printf("\ncol descr: %hhu\n", getCol(&bb, 4));
  
}

void testBitboards(){
  printf("***TESTING BITBOARDS\n");
  bitboards_init();
}

void testGetPositionOfFilled(){
  bitboard bb;
  position *p;
  int row, col;

  printf("**TESTING getPositionOfFilled\n");

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      setEmptyBitboard(&bb);
      
      setFilled(&bb, row, col);
      
      p = getPositionOfFilled(&bb);
      
      if (row != P_ROW(p) || col != P_COL(p)){
	printf("\tFAILED for row: %d, col: %d\n", row, col);
      }
    }
  }


}

int main(){

  bitboard bb;

  bbt_init();

  setEmptyBitboard(&bb);

  setFilled(&bb, 7, 7);

  setFilled(&bb, 5, 4);

  printBitboard(&bb);

  setEmpty(&bb, 7, 7);

  printBitboard(&bb);

  fillRow(&bb, 6);
  
  printBitboard(&bb);

  if (!testGetIndexOfFilled())
    fprintf(stderr, "TEST FAILED: testGetIndexOfFilled()\n");

  testFlippedBitboard();

  testRotatedBitboard();

  testGetCol();

  testBitboards();

  testGetPositionOfFilled();
}
