#ifndef ENUMERATE_MOVES_H
#define ENUMERATE_MOVES_H

#include "game_state.h"
#include "game_state_list.h"

void init_enumerations();

game_state_list * enumerate_moves(game_state*, int removeChecks);

#endif
