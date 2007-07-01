#include "game_state_list.h"
#include <stdlib.h>

game_state_list * create_gsl(){
  game_state_list *gslReturn = (game_state_list*)malloc(sizeof(game_state_list));
  gslReturn->length = 0;
  gslReturn->game_states = NULL;
  return gslReturn;
}

game_state_list * create_gsl_ofSize(int n){
  game_state_list *gslReturn = (game_state_list*)malloc(sizeof(game_state_list) +
							sizeof(game_state) * n);
  gslReturn->length = n;
  gslReturn->game_states = (game_state*)&gslReturn[1];
  return gslReturn;
}

void insert_gs(game_state_list *gsl, game_state *gs){
  /* @TODO - Make realloc increase by 2x instead of +1 */
  if (gsl->game_states == NULL){
    gsl->game_states = (game_state*)malloc(sizeof(game_state));
  } else {
    gsl->game_states = (game_state*)realloc(gsl->game_states, sizeof(game_state) *
					    (gsl->length + 1));
  }

  gsl->game_states[gsl->length] = *gs;
  gsl->length++;
}

void delete_gs(game_state_list *gsl, int index){
  int i;
  gsShallowFree(&gsl->game_states[index]);
  for (i = index; i < gsl->length - 1; i++){
    gsl->game_states[i] = gsl->game_states[i + 1];
  }

  gsl->length--;
  if (gsl->length == 0){
    free(gsl->game_states);
    gsl->game_states = NULL;
  } else {
    gsl->game_states = realloc(gsl->game_states, sizeof(game_state) * gsl->length);
  }
}

void gslDeepFree(game_state_list *gsl){
  int i;
  for (i = 0; i < gsl->length; i++){
    gsShallowFree(&gsl->game_states[i]);
  }

  free(gsl->game_states);
  free(gsl);
}
