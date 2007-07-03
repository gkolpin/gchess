#ifndef POSITION_LIST_H
#define POSITION_LIST_H

#include <stdlib.h>
#include "position.h"

typedef struct {
  position *positions;
  int length;
} position_list;

void pl_init(position_list*);
void pl_addPos(position_list*, position*);
void pl_print(position_list*);

#endif
