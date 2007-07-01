#include "boardstate.h"
#include <stdio.h>

int main(){

  bitboards_init();

  boardstate *b_state = createDefaultBoardstate();
  
  printBoardstate(b_state);

  if (getBlackPieceType(b_state, 0, 0) != ROOK){
    printf("%d\n", getWhitePieceType(b_state, 0, 0));
    fprintf(stderr, "FAILED, piece type should be rook\n");
  }
  
  if (getWhitePieceType(b_state, 7, 2) != BISHOP){
    printf("%d\n", getBlackPieceType(b_state, 7, 2));
    fprintf(stderr, "FAILED, piece type should be rook\n");
  }
  
  move m1;

  /* move white king pawn */
  setMove(&m1, 6, 4, 4, 4);
  makeBoardMove(b_state, &m1, WHITE);
  printf("\n");
  printBoardstate(b_state);

  /* move black queen pawn */
  setMove(&m1, 1, 3, 3, 3);
  makeBoardMove(b_state, &m1, BLACK);
  printf("\n");
  printBoardstate(b_state);

  /* capture black pawn */
  setMove(&m1, 4, 4, 3, 3);
  makeBoardMove(b_state, &m1, WHITE);
  printf("\n");
  printBoardstate(b_state);

  return 0;
}
