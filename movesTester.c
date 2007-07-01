#include "moves.h"
#include "util.h"
#include "move.h"
#include <stdio.h>

extern bitboard rook_col_moves[8][8][256];
extern bitboard rook_row_moves[8][8][256];
extern bitboard knight_moves[8][8];
//extern bitboard king_move_masks[8][8];

void testPawnMoves(){
  game_state *gs = createGamestate(createDefaultBoardstate(), WHITE);

  move m1;
  move m2;
  move m3;
  
  setMove(&m1, 6, 2, 5, 2);
  setMove(&m2, 6, 4, 3, 4);
  setMove(&m3, 6, 5, 5, 4);

  printf("TESTING PAWN MOVES\n");

  if (!isValidMove(gs, &m1))
    fprintf(stderr, "TEST1 FAILED\n");

  if (isValidMove(gs, &m2))
    fprintf(stderr, "TEST2 FAILED\n");

  if (isValidMove(gs, &m3))
    fprintf(stderr, "TEST3 FAILED\n");

  free(gs);
  gs = createGamestate(createDefaultBoardstate(), BLACK);
  
  setMove(&m1, 1, 2, 3, 2);
  setMove(&m2, 1, 4, 5, 4);
  setMove(&m3, 1, 5, 2, 4);

  if (!isValidMove(gs, &m1))
    fprintf(stderr, "TEST4 FAILED\n");

  if (isValidMove(gs, &m2))
    fprintf(stderr, "TEST5 FAILED\n");

  if (isValidMove(gs, &m3))
    fprintf(stderr, "TEST6 FAILED\n");


  fprintf(stderr, "PAWN TESTS FINISHED\n");
}

void testKnightMoves(){
  game_state *gs = createGamestate(createDefaultBoardstate(), WHITE);

  move m1;
  move m2;
  move m3;
  
  setMove(&m1, 7, 1, 5, 3);
  setMove(&m2, 7, 6, 5, 5);
  setMove(&m3, 7, 6, 5, 7);
  
  printf("TESTING KNIGHT MOVES\n");

  if (isValidMove(gs, &m1))
    fprintf(stderr, "TEST1 FAILED\n");
  if (!isValidMove(gs, &m2))
    fprintf(stderr, "TEST2 FAILED\n");
  if (!isValidMove(gs, &m3))
    fprintf(stderr, "TEST3 FAILED\n");

  
  fprintf(stderr, "KNIGHT TESTS FINISHED\n");
}

void testRookMoves(){
  game_state *gs = createGamestate(createDefaultBoardstate(), WHITE);

  move m1;
  move m2;
  move m3;
  move m4;
  move m5;
  move m6;

  setMove(&m1, 6, 0, 4, 0); //move white pawn legally
  setMove(&m2, 7, 0, 1, 0); //move white rook illegally
  setMove(&m3, 1, 0, 3, 0); //move black pawn
  setMove(&m4, 7, 0, 5, 0); //move white rook legally
  setMove(&m5, 0, 0, 3, 0); //move black rook illegally
  setMove(&m6, 0, 0, 1, 0); //move black rook legally

  printf("TESTING ROOK MOVES\n");

  makeMove(gs, &m1);

  //printBitboard(getFullBoard(getBoardstate(gs)));

  if (isValidMove(gs, &m2))
    fprintf(stderr, "TEST1 FAILED\n");

  makeMove(gs, &m3);

  /* printBitboard(getFullBoard(getBoardstate(gs))); */

  if (!isValidMove(gs, &m4))
    fprintf(stderr, "TEST2 FAILED\n");

  makeMove(gs, &m4);
  
  if (isValidMove(gs, &m5))
    fprintf(stderr, "TEST3 FAILED\n");

  //printBitboard(getFullBoard(getBoardstate(gs)));

  if (!isValidMove(gs, &m6))
    fprintf(stderr, "TEST4 FAILED\n");
}

void testBishopMoves(){
  game_state *gs = createGamestate(createDefaultBoardstate(), WHITE);

  move m1, m2, m3, m4, m5, m6, m7;

  setMove(&m1, 6, 4, 4, 4);     /* Move white king pawn legally */
  setMove(&m2, 1, 4, 3, 4);  	/* Move black king pawn legally */
  setMove(&m3, 7, 5, 6, 5);	/* Move white king bishop illegally */
  setMove(&m4, 7, 5, 6, 6);	/* Move white king bishop illegally */
  setMove(&m5, 7, 5, 3, 1);	/* Move white king bishop legally */
  setMove(&m6, 1, 7, 3, 7);	/* Move black pawn legally */
  setMove(&m7, 3, 1, 1, 3);	/* Move white bishop legally */

  printf("TESTING BISHOP MOVES\n");

  makeMove(gs, &m1);
  makeMove(gs, &m2);
  
  if (isValidMove(gs, &m3)){
    fprintf(stderr, "TEST 1 FAILED\n");
  }

  if (isValidMove(gs, &m4)){
    fprintf(stderr, "TEST 2 FAILED\n");
  }

  if (!isValidMove(gs, &m5)){
    fprintf(stderr, "TEST 3 FAILED\n");
  }

  makeMove(gs, &m5);
  makeMove(gs, &m6);

  if (!isValidMove(gs, &m7)){
    fprintf(stderr, "TEST 4 FAILED\n");
  }

}

void showRookMoves(){
  printf("\n\n***SHOWING ROOK MOVES\n\n");
  int row, col, descr;

  bitboard bbCur = 0;

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      for (descr = 0; descr < 256; descr++){
	bbCur |= rook_col_moves[row][col][descr];
	bbCur |= rook_row_moves[row][col][descr];
	printBitboard(&bbCur);
	bbCur = 0;
      }
    }
  }
}

void showKnightMoves(){
  printf("\n\n***SHOWING ROOK MOVES\n\n");
  int row, col, descr;

  bitboard bbCur = 0;

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      printf("\n\n%d %d\n\n", row, col);
      
      bbCur = knight_moves[row][col];
      printBitboard(&bbCur);
    }
  }
}

void testQueenMoves(){}

void testKingMoves(){

}

int main(){

  bb_init();

  testPawnMoves();

  testKnightMoves();

  testRookMoves();

  testBishopMoves();

  testQueenMoves();

  testKingMoves();

  //  showRookMoves();

  //  showKnightMoves();

  return 0;
}
