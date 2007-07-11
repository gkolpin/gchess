#include "move.h"
#include "boardstate.h"

void setMove(move *m, short oldRow, short oldCol,
		short newRow, short newCol){

  m->oldRow = oldRow;
  m->oldCol = oldCol;
  m->newRow = newRow;
  m->newCol = newCol;
  m->pawnPromotion = NULL_PIECE;
  m->capturedPiece = NULL_PIECE;
}

void setMoveWithPromotion(move *m, short oldRow, short oldCol,
			  short newRow, short newCol, piece p){
  setMove(m, oldRow, oldCol, newRow, newCol);
  m->pawnPromotion = p;
  m->capturedPiece = NULL_PIECE;
}

void setMoveForHistory(move *m, short oldRow, short oldCol,
		       short newRow, short newCol, piece pawnPromotion,
		       piece capturedPiece){
  setMoveWithPromotion(m, oldRow, oldCol, newRow, newCol, pawnPromotion);
  m->capturedPiece = capturedPiece;
}


move * createMove(short oldRow, short oldCol,
		  short newRow, short newCol){
 
  move *returnval = (move*)malloc(sizeof(move));
  
  returnval->oldRow = oldRow;
  returnval->oldCol = oldCol;
  returnval->newRow = newRow;
  returnval->newCol = newCol;
  returnval->pawnPromotion = NULL_PIECE;
  returnval->capturedPiece = NULL_PIECE;

  return returnval; 
}
