#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "boardstate.h"
#include "game_state_list.h"
#include "move.h"

typedef struct game_state{

  boardstate *b_state;
  
  color player_to_move;

  int en_passante;
  
} game_state;

game_state * createGamestate(boardstate*, color player_to_move);
game_state * createDefaultGamestate();
color getPlayerToMove(game_state*);
void setPlayerToMove(game_state*, color);
boardstate * getBoardstate(game_state*);
int gs_isSpaceFilled(game_state*, int row, int col);
int en_passante(game_state*);
void makeMove(game_state*, move*);
void gs_undoMove(game_state*, move*);
/* the second argument is a 2-d array of bitboards. The first
 slot is the old piece location, the second is the new. */
void makeMoveUsingBB(game_state*, bitboard**);
struct game_state_list * copyGameStates(game_state*, int);
game_state * gs_deepCopy(game_state*);
void gsShallowFree(game_state*);
void printGameState(game_state*);
int gsEquals(game_state*, game_state*);

int isValidMove(game_state*, move*);
int isCheckMate(game_state*, color forColor);
int isKingInCheck(game_state*, color);

#endif
