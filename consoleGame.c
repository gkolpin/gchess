#include <stdlib.h>
#include <stdio.h>

#include "enumerate_moves.h"
#include "bitboard.h"
#include "game_state.h"
#include "move.h"
#include "boardstate.h"

void promptForMove(move*);
void makeComputerMove(game_state**);
void gameOver(color);

void init(){
  srandomdev();

  init_enumerations();
  bb_init();
}

int main(){
  init();
  game_state *gs = createDefaultGamestate();

  color cPlayer = WHITE;
  color cComputer = BLACK;

  move m;

  while (1){
    printGameState(gs);
  
    while (1){
      promptForMove(&m);
      if (isValidMove(gs, &m)){
	makeMove(gs, &m);
	break;
      }
    }
    
    if (isCheckMate(gs, cPlayer)){
      gameOver(WHITE);
    }

    printGameState(gs);
    
    makeComputerMove(&gs);
    
    if (isCheckMate(gs, cComputer)){
      gameOver(BLACK);
    }
  }

  return 0;
}

void promptForMove(move *m){
  int oldRow, oldCol, newRow, newCol;
  printf("Enter move:\n");
  scanf("%d %d %d %d", &oldRow, &oldCol, &newRow, &newCol);
  setMove(m, oldRow, oldCol, newRow, newCol);
}

void makeComputerMove(game_state **gs){
  game_state_list *gslPotentialMoves = enumerate_moves(*gs, 1);
  int r;
  
  long MAX = (1 << 31) - 1;

  r = (int)((random() / (float)MAX) * gslPotentialMoves->length);

  *gs = gs_deepCopy(&gslPotentialMoves->game_states[r]);
  
  gslDeepFree(gslPotentialMoves);

}

void gameOver(color winner){
  if (winner == WHITE){
    printf("\n****WHITE WINS!!\n");
  } else {
    printf("\n****BLACK WINS!!\n");
  }
  
  exit(0);
}
