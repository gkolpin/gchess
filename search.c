#include "search.h"
#include "enumerate_moves.h"
#include "game_state.h"
#include "eval.h"

game_state * search(game_state *gs, color c, int max_search_depth){
  int i, iTemp, curHighest = -1000;
  int curHighestIndex = -1;
  game_state *gsTemp;

  game_state_list *gs_list;
  gs_list = enumerate_moves(gs, 1);
  for (i = 0; i < gs_list->length; i++){
    /* we're looking for the highest score */
    iTemp = scoreSearch(&gs_list->game_states[i], c, max_search_depth, 1);
    if (iTemp > curHighest){
      curHighest = iTemp;
      curHighestIndex = i;
    }
  }

  if (curHighestIndex == -1){
    curHighestIndex = 0;
  }
   
  gsTemp = gs_deepCopy(&gs_list->game_states[curHighestIndex]);

  gslDeepFree(gs_list);

  return gsTemp;
}

int scoreSearch(game_state *gs, color c, int max_search_depth, int curDepth){
  int i, curHighest = -4000, iTemp, curLowest = 4000;
  game_state *gsTemp;
  game_state_list *gs_list;

  //printGameState(gs);

  if (curDepth >= max_search_depth){
    if (getPlayerToMove(gs) == c){
      /* we want the highest */
      gs_list = enumerate_moves(gs, 1);
      for (i = 0; i < gs_list->length; i++){
	iTemp = eval(&gs_list->game_states[i], c);
	//printGameState(&gs_list->game_states[i]);
	if (iTemp > curHighest){
	  curHighest = iTemp;
	}
      }

      if (gs_list->length == 0){
	gslDeepFree(gs_list);
	return -4000;
      }

      gslDeepFree(gs_list);

      return curHighest;
    } else {
      /* we want the lowest */
      gs_list = enumerate_moves(gs, 1);
      for (i = 0; i < gs_list->length; i++){
	iTemp = eval(&gs_list->game_states[i], c);
	//printGameState(&gs_list->game_states[i]);
	if (iTemp < curLowest){
	  curLowest = iTemp;
	}
      }

      if (gs_list->length == 0){
	gslDeepFree(gs_list);
	return 4000;
      }

      gslDeepFree(gs_list);

      return curLowest;
    }
  } else {
    /* recurse */
    if (getPlayerToMove(gs) == c){
      /* want the highest */
      gs_list = enumerate_moves(gs, 1);
      for (i = 0; i < gs_list->length; i++){
	gsTemp = gs_deepCopy(&gs_list->game_states[i]);
	iTemp = scoreSearch(gsTemp, c, max_search_depth, curDepth + 1);
	gsShallowFree(gsTemp);
	free(gsTemp);
	if (iTemp > curHighest){
	  curHighest = iTemp;
	}
      }
      gslDeepFree(gs_list);

      return curHighest;
    } else {
      /* want the lowest */
      gs_list = enumerate_moves(gs, 1);
      for (i = 0; i < gs_list->length; i++){
	gsTemp = gs_deepCopy(&gs_list->game_states[i]);
	iTemp = scoreSearch(gsTemp, c, max_search_depth, curDepth + 1);
	gsShallowFree(gsTemp);
	free(gsTemp);
	if (iTemp < curLowest){
	  curLowest = iTemp;
	}
      }
      gslDeepFree(gs_list);

      return curLowest;
    }
  }


}
