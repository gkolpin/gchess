#include "game_state.h"
#include "game_state_list.h"
#include <stdlib.h>

static void resize_grow(game_state_list*);
static void resize_shrink(game_state_list*);

static void resize_grow(game_state_list *gsl){
  if (gsl->game_states == NULL){
    gsl->game_states = (game_state**)malloc(sizeof(game_state*));
    gsl->l_alloc = 1;
  } else {
    gsl->game_states = (game_state**)realloc(gsl->game_states, 
						  gsl->l_alloc * 2 * 
						  sizeof(game_state*));
    gsl->l_alloc = gsl->l_alloc * 2;
  }
}

static void resize_shrink(game_state_list *gsl){
  gsl->game_states = (game_state**)realloc(gsl->game_states, 
						sizeof(game_state*) * 
						(gsl->l_alloc >> 1));
  gsl->l_alloc >>= 1;
}

game_state_list * create_gsl(){
  game_state_list *gslReturn = (game_state_list*)malloc(sizeof(game_state_list));
  gslReturn->length = 0;
  gslReturn->l_alloc = 0;
  gslReturn->game_states = NULL;
  return gslReturn;
}

game_state_list * create_gsl_ofSize(int n){
  game_state_list *gslReturn = (game_state_list*)malloc(sizeof(game_state_list) +
							sizeof(game_state*) * n);
  gslReturn->length = n;
  gslReturn->l_alloc = n;
  gslReturn->game_states = (game_state**)&gslReturn[1];
  return gslReturn;
}

void insert_gs(game_state_list *gsl, game_state *gs){
  if (gsl->l_alloc <= gsl->length){
    resize_grow(gsl);
  }

  gsl->game_states[gsl->length] = gs;
  gsl->length++;
}

void delete_gs(game_state_list *gsl, int index){
  int i;
  gsShallowFree(gsl->game_states[index]);
  free(gsl->game_states[index]);

  for (i = index; i < gsl->length - 1; i++){
    gsl->game_states[i] = gsl->game_states[i + 1];
  }

  gsl->length--;
  if (gsl->length == 0){
    free(gsl->game_states);
    gsl->game_states = NULL;
    gsl->l_alloc = 0;
  } else if (gsl->length <= (gsl->l_alloc >> 1)){
    resize_shrink(gsl);
  }
}

void gslDeepFree(game_state_list *gsl){
  int i;
  for (i = 0; i < gsl->length; i++){
    gsShallowFree(gsl->game_states[i]);
    free(gsl->game_states[i]);
  }

  free(gsl->game_states);
  free(gsl);
}
