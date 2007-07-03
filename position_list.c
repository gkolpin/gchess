#include "position.h"
#include "position_list.h"

void pl_init(position_list *pl){
  pl->positions = NULL;
  pl->length = 0;
}

void pl_addPos(position_list *pl, position *p){
  if (pl->length == 0){
    pl->positions = (position*)malloc(sizeof(position));
    pl->positions[0] = *p;
    pl->length++;
  } else {
    pl->positions = (position*)realloc(pl->positions, 
				       sizeof(position) * (pl->length + 1));
    pl->positions[pl->length] = *p;
    pl->length++;
  }
}

void pl_print(position_list *pl){
  int i;
  for (i = 0; i < pl->length; i++){
    pos_print(&pl->positions[i]);
    printf("\n");
  }
}
