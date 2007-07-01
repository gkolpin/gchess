#include "eval.h"
#include "piece.h"
#include "game_state.h"
#include "boardstate.h"

/* the engine's position evaluation function */
int eval(game_state *gs, color c){
  /* for now this will be a very simple implentation - 
     we will count the numbers of each piece and multiply by 
     their material values */

  int i, whiteScore = 0, blackScore = 0, multiplier;
  bitboard_list *whiteLists, *blackLists;

  boardstate *bs = getBoardstate(gs);
  whiteLists = getBitboardLists(bs, WHITE);
  blackLists = getBitboardLists(bs, BLACK);

  for (i = 0; i < PIECE_TYPES; i++){
    switch (i){
    case PAWN:
      multiplier = 1;
      break;
    case KNIGHT:
      multiplier = 3;
      break;
    case BISHOP:
      multiplier = 3;
      break;
    case ROOK:
      multiplier = 5;
      break;
    case QUEEN: 
      multiplier = 9;
      break;
    }

    whiteScore += whiteLists[i].length * multiplier;
    blackScore += blackLists[i].length * multiplier;
  }

  return c == WHITE ? whiteScore - blackScore : 
    blackScore - whiteScore;  
}
