#include "enumerate_moves.h"
#include "game_state_list.h"
#include "game_state.h"
#include "boardstate.h"
#include "bitboards.h"

#include <stdio.h>

void bs_placePiece(boardstate *bs, color c, piece p, int row, int col);

void testKingBishopCheck(){
  boardstate *bs = createEmptyBoardstate();
  
  bs_placePiece(bs, WHITE, BISHOP, 3, 3);
  bs_placePiece(bs, BLACK, KING, 0, 1);
  bs_placePiece(bs, WHITE, KING, 7, 7);

  printBoardstate(bs);
  printf("\n\n");

  game_state *gs = createGamestate(bs, BLACK);

  game_state_list *gsl = enumerate_moves(gs, 1);

  int i;
  for (i = 0; i < gsl->length; i++){
    printGameState(&gsl->game_states[i]);
  }
}

void testQueenCapture(){
  boardstate *bs = createEmptyBoardstate();
  
  /* place kings */
  bs_placePiece(bs, WHITE, KING, 7, 7);
  bs_placePiece(bs, BLACK, KING, 1, 1);

  /* place black queen */
  bs_placePiece(bs, BLACK, QUEEN, 6, 2);

  /* place white rook */
  bs_placePiece(bs, WHITE, ROOK, 6, 6);

  game_state *gs = createGamestate(bs, WHITE);

  printGameState(gs);
  printf("\n\n");
  printBitboard(&bs->allBlack);
  printf("\n\n");
  printBitboard(&pos[6][2]);
  printf("\n\n");

  move m;
  setMove(&m, 6, 6, 6, 2);
  makeMove(gs, &m);

  printGameState(gs);
}

/* not complete */
void testPawnPromotion(){
  boardstate *bs = createEmptyBoardstate();
  
  /* place kings */
  bs_placePiece(bs, WHITE, KING, 7, 7);
  bs_placePiece(bs, BLACK, KING, 1, 1);

  /* place white pawn */
  bs_placePiece(bs, WHITE, PAWN, 1, 5);

  game_state *gs = createGamestate(bs, WHITE);

  printGameState(gs);
  printf("\n\n");

  move m;
  setMoveWithPromotion(&m, 1, 5, 0, 5, QUEEN);
  makeMove(gs, &m);

  printGameState(gs);
}

void init(){
  init_enumerations();
  bb_init();
}

int main(){

  init();

  //testKingBishopCheck();
  //testQueenCapture();
  testPawnPromotion();

  return 0;
}
