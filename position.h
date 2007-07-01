#ifndef POSITION_H
#define POSITION_H

typedef struct{
  int row, col;
} position;

#define P_ROW(pos) (pos)->row
#define P_COL(pos) (pos)->col

#define P_SET_ROW(pos, i_row) (pos)->row = i_row
#define P_SET_COL(pos, i_col) (pos)->col = i_col

#endif
