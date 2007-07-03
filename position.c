#include "position.h"

void pos_print(position *pos){
  printf("[%d, %d]", P_ROW(pos), P_COL(pos));
}
