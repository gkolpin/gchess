#ifndef MOVE_H
#define MOVE_H

#include "piece.h"

typedef struct{
  short oldRow, oldCol;
  short newRow, newCol;
  piece pawnPromotion;
} move;

#define GET_PAWN_PROMOTION(m) m->pawnPromotion

void setMove(move *m, short oldRow, short oldCol, 
		short newRow, short newCol);

void setMoveWithPromotion(move *m, short oldRow, short oldCol,
			  short newRow, short newCol, piece p);

move * createMove(short oldRow, short oldCol,
		  short newrow, short newCol);



#endif
