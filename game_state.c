#include "game_state_list.h"
#include "game_state.h"
#include "enumerate_moves.h"
#include "move.h"

#include <stdio.h>
#include <stdlib.h>

game_state * createGamestate(boardstate *b_state, color player_to_move){

  game_state *returnval = (game_state*)malloc(sizeof(game_state));

  returnval->b_state = b_state;
  returnval->player_to_move = player_to_move;
  returnval->en_passante = 0;

}

game_state * createDefaultGamestate(){
  game_state *gsReturn = createGamestate(createDefaultBoardstate(), WHITE);
  return gsReturn;
}

color getPlayerToMove(game_state *gs){
  return gs->player_to_move;
}

void setPlayerToMove(game_state *gs, color c){
  gs->player_to_move = c;
}

boardstate * getBoardstate(game_state *gs){
  return gs->b_state;
}

int en_passante(game_state *gs){
  return gs->en_passante;
}

int gs_isSpaceFilled(game_state *gs, int row, int col){
  return bs_isSpaceFilled(gs->b_state, row, col);
}

void makeMove(game_state *gs, move *m){
  makeBoardMove(gs->b_state, m, gs->player_to_move);

  if (gs->player_to_move == WHITE)
    gs->player_to_move = BLACK;

  else
    gs->player_to_move = WHITE;
}

void gs_undoMove(game_state *gs, move *m){
  gs->player_to_move = gs->player_to_move == WHITE ? BLACK : WHITE;
  bs_undoMove(gs->b_state, m, gs->player_to_move);
}

/* void makeMoveUsingBB(game_state *gs, bitboard *move){ */
/*   makeBoardMoveUsingBB(gs->b_state, move, gs->player_to_move); */
  
/*   if (gs->player_to_move == WHITE){ */
/*     gs->player_to_move = BLACK; */
/*   } */
/*   else { */
/*     gs->player_to_move = WHITE; */
/*   } */
/* } */

game_state * gs_deepCopy(game_state *gs){
  game_state *gsReturn = (game_state*)malloc(sizeof(game_state));
  gsReturn->player_to_move = gs->player_to_move;
  gsReturn->en_passante = gs->en_passante;
  gsReturn->b_state = bs_deepCopy(gs->b_state);
  return gsReturn;
}

void gsShallowFree(game_state *gs){
  bsShallowFree(gs->b_state);
  free(gs->b_state);
}

void gs_deepCopyTo(game_state *gs, game_state *receiver){
  receiver->player_to_move = gs->player_to_move;
  receiver->en_passante = gs->en_passante;
  receiver->b_state = bs_deepCopy(gs->b_state);
}

game_state_list * copyGameStates(game_state *gs, int n){
  game_state_list *gslReturn = create_gsl_ofSize(n);
  int i;
  for (i = 0; i < n; i++){
    gs_deepCopyTo(gs, gslReturn->game_states[i]);
  }
  gslReturn->length = n;
  return gslReturn;
}

void printGameState(game_state *gs){
  printBoardstate(getBoardstate(gs));
  printf("\n\n");
}

int gsEquals(game_state *gs1, game_state *gs2){
  if (bsEquals(gs1->b_state, gs2->b_state) &&
      gs1->player_to_move == gs2->player_to_move &&
      gs1->en_passante == gs2->en_passante){

    return 1;
  }
  
  return 0;
}

int isValidMove(game_state *g_state, move *m){
  int iReturn = 0;
  game_state_list *gsl = enumerate_moves(g_state, 1);
  game_state *gsTemp = gs_deepCopy(g_state);

  makeMove(gsTemp, m);

  int i;
  for (i = 0; i < gsl->length; i++){
    if (gsEquals(gsTemp, gsl->game_states[i])){
      iReturn = 1;
      break;
    }
  }

  gslDeepFree(gsl);
  gsShallowFree(gsTemp);
  free(gsTemp);

  return iReturn;
}

int isCheckMate(game_state *gs, color forColor){
  int iReturn = 0;
  color otherColor = forColor == WHITE ? BLACK : WHITE;

  /* if otherColor has no enumerated moves and it's king is in
     check, then it must be checkmated. */

  game_state *gsTemp = gs_deepCopy(gs);
  setPlayerToMove(gsTemp, otherColor);
  game_state_list *gsl = enumerate_moves(gsTemp, 1);

  if (gsl->length == 0 && isKingInCheck(gs, otherColor)){
    return iReturn = 1;
  }
  
  gslDeepFree(gsl);
  gsShallowFree(gsTemp);
  free(gsTemp);

  return iReturn;
}

int isKingInCheck(game_state *gs, color c){
  /* enumerate other color's moves and see if any collide
     with c's king. */
  int iReturn = 0;

  color otherColor = c == WHITE ? BLACK : WHITE;
  
  game_state *gsTemp = gs_deepCopy(gs);
  setPlayerToMove(gsTemp, otherColor);
  game_state_list *gsl = enumerate_moves(gsTemp, 0);
  
  /* get king's position */
  boardstate *bsTemp = getBoardstate(gs);
  bitboard king_pos = BS_KING_POS(bsTemp, c);

  int i;
  for (i = 0; i < gsl->length; i++){
    if ((otherColor == WHITE ? getAllWhite(getBoardstate(gsl->game_states[i]))[0] :
	 getAllBlack(getBoardstate(gsl->game_states[i]))[0])
	& king_pos){

      iReturn = 1;
      break;
    }
  }

  gslDeepFree(gsl);
  gsShallowFree(gsTemp);
  free(gsTemp);

  return iReturn;
}
