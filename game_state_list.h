#ifndef GAME_STATE_LIST_H
#define GAME_STATE_LIST_H

#include "game_state.h"

typedef struct game_state_list {
  struct game_state *game_states;
  int length;
} game_state_list;

game_state_list * create_gsl();
game_state_list * create_gsl_ofSize(int n);
void insert_gs(game_state_list*, struct game_state*);
void delete_gs(game_state_list*, int);
void gslDeepFree(game_state_list*);

#endif
