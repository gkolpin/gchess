#include "boardstate.h"
#include "move.h"
#include "types.h"
#include "bitboards.h"
#include "bitboard.h"
#include "position.h"

#include <string.h>

/* Used as helpers for keeping lists of individual pieces
within the boardstate. */
void bs_placePiece(boardstate*, color, piece, int row, int col);
void bs_removePiece(boardstate*, int row, int col);
void bs_fillRowWithPiece(boardstate*, color, piece, int row);

boardstate * createEmptyBoardstate(){
  boardstate *bsReturn = (boardstate*)calloc(1, sizeof(boardstate));
  return bsReturn;
}

boardstate * createDefaultBoardstate(){
  boardstate * returnval;
  
  int i;

  returnval = (boardstate*)malloc(sizeof(boardstate));

  for (i = 0; i < PIECE_TYPES; i++){
    setEmptyBitboard(&returnval->whitePieces[i]);
    setEmptyBitboard(&returnval->blackPieces[i]);
    
    initialize_bbl(&returnval->whiteLists[i]);
    initialize_bbl(&returnval->blackLists[i]);
  }

  setEmptyBitboard(&returnval->fullBoard);
  setEmptyBitboard(&returnval->allWhite);
  setEmptyBitboard(&returnval->allBlack);

  //set up pawns

  bs_fillRowWithPiece(returnval, WHITE, PAWN, 6);
  bs_fillRowWithPiece(returnval, BLACK, PAWN, 1);

  //set up knights
  
  bs_placePiece(returnval, WHITE, KNIGHT, 7, 1);
  bs_placePiece(returnval, WHITE, KNIGHT, 7, 6);
  bs_placePiece(returnval, BLACK, KNIGHT, 0, 1);
  bs_placePiece(returnval, BLACK, KNIGHT, 0, 6);

  //set up bishops
  
  bs_placePiece(returnval, WHITE, BISHOP, 7, 2);
  bs_placePiece(returnval, WHITE, BISHOP, 7, 5);
  bs_placePiece(returnval, BLACK, BISHOP, 0, 2);
  bs_placePiece(returnval, BLACK, BISHOP, 0, 5);

  //set up rooks

  bs_placePiece(returnval, WHITE, ROOK, 7, 0);
  bs_placePiece(returnval, WHITE, ROOK, 7, 7);
  bs_placePiece(returnval, BLACK, ROOK, 0, 0);
  bs_placePiece(returnval, BLACK, ROOK, 0, 7);
  
  //set up queens

  bs_placePiece(returnval, WHITE, QUEEN, 7, 3);
  bs_placePiece(returnval, BLACK, QUEEN, 0, 3);
  
  //set up kings

  bs_placePiece(returnval, WHITE, KING, 7, 4);
  bs_placePiece(returnval, BLACK, KING, 0, 4);
    
  return returnval;
}

void setDefaultBoardstate(boardstate *b_state){
  int i;

  for (i = 0; i < PIECE_TYPES; i++){
    setEmptyBitboard(&b_state->whitePieces[i]);
    setEmptyBitboard(&b_state->blackPieces[i]);
  }

  //set up pawns
  
  fillRow(&b_state->whitePieces[PAWN], 6);
  fillRow(&b_state->blackPieces[PAWN], 1);

  //set up knights
  
  setFilled(&b_state->whitePieces[KNIGHT], 7, 1);
  setFilled(&b_state->whitePieces[KNIGHT], 7, 6);
  setFilled(&b_state->blackPieces[KNIGHT], 0, 1);
  setFilled(&b_state->blackPieces[KNIGHT], 0, 6);


  //set up bishops
  
  setFilled(&b_state->whitePieces[BISHOP], 7, 2);
  setFilled(&b_state->whitePieces[BISHOP], 7, 5);
  setFilled(&b_state->blackPieces[BISHOP], 0, 2);
  setFilled(&b_state->blackPieces[BISHOP], 0, 5);

  //set up rooks
  
  setFilled(&b_state->whitePieces[ROOK], 7, 0);
  setFilled(&b_state->whitePieces[ROOK], 7, 7);
  setFilled(&b_state->blackPieces[ROOK], 0, 0);
  setFilled(&b_state->blackPieces[ROOK], 0, 7);
  
  //set up queens

  setFilled(&b_state->whitePieces[QUEEN], 7, 3);
  setFilled(&b_state->blackPieces[QUEEN], 0, 3);
  
  //set up kings
  
  setFilled(&b_state->whitePieces[KING], 7, 4);
  setFilled(&b_state->blackPieces[KING], 0, 4);

  setEmptyBitboard(&b_state->fullBoard);
  setEmptyBitboard(&b_state->allWhite);
  setEmptyBitboard(&b_state->allBlack);

  union_bbSet(b_state->whitePieces, 6, &b_state->allWhite);
  union_bbSet(b_state->blackPieces, 6, &b_state->allBlack);

  union_bb(&b_state->allWhite, &b_state->allBlack, &b_state->fullBoard);


}


piece getPieceType(boardstate *bs, color c, int row, int col){
  int i;

  if (c == WHITE){
    i =  (piece)getIndexOfFilled(bs->whitePieces, PIECE_TYPES, 
				 row, col);
    
    if (i == -1)
      return NULL_PIECE;
    else
      return (piece)i;
  }
  else {
    i = (piece)getIndexOfFilled(bs->blackPieces, PIECE_TYPES,
				row, col);
    
    if (i == -1)
      return NULL_PIECE;
    else
      return (piece)i;
  }
}

piece getWhitePieceType(boardstate *bs, int row, int col){
  return getPieceType(bs, WHITE, row, col);
}

piece getBlackPieceType(boardstate *bs, int row, int col){
  return getPieceType(bs, BLACK, row, col);
}

bitboard * getAllWhite(boardstate *bs){
  return &bs->allWhite;
}

bitboard * getAllBlack(boardstate *bs){
  return &bs->allBlack;
}

bitboard * getFullBoard(boardstate *bs){
  return &bs->fullBoard;
}

bitboard_list * getBitboardLists(boardstate *bs, color c){
  return c == WHITE ? bs->whiteLists : bs->blackLists;
}

bitboard * getPawns(boardstate *bs, color c){
  return c == WHITE ? &bs->whitePieces[PAWN] : 
    &bs->blackPieces[PAWN];
}

int bs_isSpaceFilled(boardstate *bs, int row, int col){
  return isFilled(&bs->fullBoard, row, col);
}

void printBoardstate(boardstate * b_state){
  char board[8][8];
  
  int i, j, k;
  
  for (i = 0; i < 8; i++){
    for (j = 0; j < 8; j++){
      board[i][j] = '0';
    }
  }

  for (i = 0; i < PIECE_TYPES; i++){
    
    for (j = 0; j < 8; j++){
      for (k = 0; k < 8; k++){
	
	if (isFilled(&b_state->whitePieces[i], j, k)){
	  
	  switch(i){

	  case PAWN:{
	    board[j][k] = 'P';
	    break;
	  }
	    
	  case KNIGHT: {
	    board[j][k] = 'N';
	    break;
	  }
	    
	  case BISHOP: {
	    board[j][k] = 'B';
	    break;
	  }

	  case ROOK: {
	    board[j][k] = 'R';
	    break;
	  }
	    
	  case QUEEN: {
	    board[j][k] = 'Q';
	    break;
	  }
	    
	  case KING: {
	    board[j][k] = 'K';
	    break;
	  }
	    
	  } //end switch
	}
      }
    }
  }
  
  for (i = 0; i < PIECE_TYPES; i++){
    
    for (j = 0; j < 8; j++){
      for (k = 0; k < 8; k++){
	
	if (isFilled(&b_state->blackPieces[i], j, k)){
	  
	  switch(i){
	    
	  case PAWN:{
	    board[j][k] = 'p';
	    break;
	  }
	    
	  case KNIGHT: {
	    board[j][k] = 'n';
	    break;
	  }
	    
	  case BISHOP: {
	    board[j][k] = 'b';
	    break;
	  }

	  case ROOK: {
	    board[j][k] = 'r';
	    break;
	  }
	    
	  case QUEEN: {
	    board[j][k] = 'q';
	    break;
	  }

	  case KING: {
	    board[j][k] = 'k';
	    break;
	  }
	    
	  } //end switch
	}
      }
    }
  }
  
  for (i = 0; i < 8; i++){
    for (j = 0; j < 8; j++){
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}

void bs_placePiece(boardstate *bs, color c, piece p, int row, int col){
  bitboard place = pos[row][col];
  if (c == WHITE){
    /* First place the piece within whiteLists */
    insert_bb(&bs->whiteLists[p], &place);

    /* Now place it within whitePieces */
    bs->whitePieces[p] |= place;

    /* Now place it on full board */
    bs->fullBoard |= place;
    
    /* Finally place it in allWhite */
    bs->allWhite |= place;

  }
  else {
    /* Same as above, except replace white with black */

    insert_bb(&bs->blackLists[p], &place);
    
    bs->blackPieces[p] |= place;
    
    bs->fullBoard |= place;

    bs->allBlack |= place;
  }
}

void bs_removePiece(boardstate *bs, int row, int col){
  color cPiece = bs->allWhite & pos[row][col] ? WHITE : BLACK;
  piece p = getPieceType(bs, cPiece, row, col);
  
  bitboard_list *bbCurList;
  int i;
  if (cPiece == WHITE){
    bbCurList = &bs->whiteLists[p];
    delete_bb_at(bbCurList, bbl_GetIndexOf(bbCurList, pos[row][col]));
    bs->whitePieces[p] ^= pos[row][col];
    bs->fullBoard ^= pos[row][col];
    bs->allWhite ^= pos[row][col];
  } else {
    bbCurList = &bs->blackLists[p];
    delete_bb_at(bbCurList, bbl_GetIndexOf(bbCurList, pos[row][col]));
    bs->blackPieces[p] ^= pos[row][col];
    bs->fullBoard ^= pos[row][col];
    bs->allBlack ^= pos[row][col];
  }
}

void bs_fillRowWithPiece(boardstate *bs, color c, piece p, int row){
  bitboard bbTemp;
  bitboard_list *bblTemp;

  setEmptyBitboard(&bbTemp);
  fillRow(&bbTemp, row);

  bblTemp = get_bitboard_list_pointer(&bbTemp);

  if (c == WHITE){
    insert_bbl_into(&bs->whiteLists[p], bblTemp);

    bs->whitePieces[p] |= bbTemp;

    bs->fullBoard |= bbTemp;

    bs->allWhite |= bbTemp;
  }
  else {
    insert_bbl_into(&bs->blackLists[p], bblTemp);

    bs->blackPieces[p] |= bbTemp;

    bs->fullBoard |= bbTemp;

    bs->allBlack |= bbTemp;
  }

  free_bbl(bblTemp);
}

int isCapture(boardstate *bs, move *m, color side_to_move){
  if (side_to_move == WHITE){
    return (bs->allBlack & pos[m->newRow][m->newCol]) != 0 ? 1 : 0;
  } else {
    return (bs->allWhite & pos[m->newRow][m->newCol]) != 0 ? 1 : 0;
  }
}

/* int isCaptureUsingBB(boardstate *bs, bitboard *move, color side_to_move){ */
/*   if (side_to_move == WHITE){ */
/*     return bs->allBlack & move[1]; */
/*   } else { */
/*     return bs->allWhite & move[1]; */
/*   } */
/* } */

int findBBLIndexOfPosition(bitboard_list *bbl, bitboard *bb){
  int i;
  for (i = 0; i < bbl->length; i++){
    if (bbl->bitboards[i] == *bb){
      return i;
    }
  }

  return -1;
}

void makeBoardMoveCapture(boardstate *bs, move *m, color side_to_move){
  int idx;
  bitboard inverted_old_pos = inverse[m->oldRow][m->oldCol];
  bitboard new_pos = pos[m->newRow][m->newCol];

  piece piece_to_move = getPieceType(bs, side_to_move, m->oldRow, m->oldCol);
  if (piece_to_move == NULL_PIECE){
    return;
  }
  
  bitboard_list *bbl_colorToMove;
  bitboard_list *bbl_colorToCapture;
  bitboard *bb_colorToMove;
  bitboard *bb_colorToCapture;

  if (side_to_move == WHITE){
    bbl_colorToMove = &bs->whiteLists[piece_to_move];
    bbl_colorToCapture = &bs->blackLists[idx = getIndexOfFilled(bs->blackPieces, 
								PIECE_TYPES, 
								m->newRow,
								m->newCol)];
    bb_colorToMove = &bs->whitePieces[piece_to_move];
    bb_colorToCapture = &bs->blackPieces[idx];

    /* all white and all black */
    bs->allWhite &= inverted_old_pos;
    bs->allWhite |= new_pos;

    bs->allBlack ^= new_pos;
  } else {
    bbl_colorToMove = &bs->blackLists[piece_to_move];
    bbl_colorToCapture = &bs->whiteLists[idx = getIndexOfFilled(bs->whitePieces, 
								PIECE_TYPES,
								m->newRow,
								m->newCol)];
    bb_colorToMove = &bs->blackPieces[piece_to_move];
    bb_colorToCapture = &bs->whitePieces[idx];

    /* all white and all black */
    bs->allBlack &= inverted_old_pos;
    bs->allBlack |= new_pos;

    bs->allWhite ^= new_pos;
  }

  /* perform full board move */
  bs->fullBoard &= inverted_old_pos;
  bs->fullBoard |= new_pos;

  /* bbl colorToMove */
  idx = findBBLIndexOfPosition(bbl_colorToMove, &pos[m->oldRow][m->oldCol]);
  bbl_colorToMove->bitboards[idx] &= inverted_old_pos;
  bbl_colorToMove->bitboards[idx] |= new_pos;

  /* bbl to capture */
  idx = findBBLIndexOfPosition(bbl_colorToCapture, &pos[m->newRow][m->newCol]);
  delete_bb_at(bbl_colorToCapture, idx);

  /* bb color to move */
  *bb_colorToMove &= inverted_old_pos;
  *bb_colorToMove |= new_pos;

  /* bb color to capture */
  *bb_colorToCapture ^= new_pos;
}

/* void makeBoardMoveCaptureUsingBB(boardstate *bs, bitboard *move, color side_to_move){ */
/*   int idx; */
/*   bitboard inverted_old_pos = move[0]; */
/*   bitboard new_pos = pos[m->newRow][m->newCol]; */

/*   piece piece_to_move = getPieceType(bs, side_to_move, m->oldRow, m->oldCol); */
  
/*   bitboard_list *bbl_colorToMove; */
/*   bitboard_list *bbl_colorToCapture; */
/*   bitboard *bb_colorToMove; */
/*   bitboard *bb_colorToCapture; */

/*   if (side_to_move == WHITE){ */
/*     bbl_colorToMove = &bs->whiteLists[piece_to_move]; */
/*     bbl_colorToCapture = &bs->blackLists[idx = getIndexOfFilled(bs->blackPieces,  */
/* 								PIECE_TYPES,  */
/* 								m->newRow, */
/* 								m->newCol)]; */
/*     bb_colorToMove = &bs->whitePieces[piece_to_move]; */
/*     bb_colorToCapture = &bs->blackPieces[idx]; */
/*   } else { */
/*     bbl_colorToMove = &bs->blackLists[piece_to_move]; */
/*     bbl_colorToCapture = &bs->whiteLists[idx = getIndexOfFilled(bs->whitePieces,  */
/* 								PIECE_TYPES, */
/* 								m->newRow, */
/* 								m->newCol)]; */
/*     bb_colorToMove = &bs->blackPieces[piece_to_move]; */
/*     bb_colorToCapture = &bs->whitePieces[idx]; */
/*   } */

/*   /\* perform full board move *\/ */
/*   bs->fullBoard &= inverted_old_pos; */
/*   bs->fullBoard |= new_pos; */

/*   /\* bbl colorToMove *\/ */
/*   idx = findBBLIndexOfPosition(bbl_colorToMove, &pos[m->oldRow][m->oldCol]); */
/*   bbl_colorToMove->bitboards[idx] &= inverted_old_pos; */
/*   bbl_colorToMove->bitboards[idx] |= new_pos; */

/*   /\* bbl to capture *\/ */
/*   idx = findBBLIndexOfPosition(bbl_colorToCapture, &pos[m->oldRow][m->oldCol]); */
/*   delete_bb_at(bbl_colorToCapture, idx); */

/*   /\* bb color to move *\/ */
/*   *bb_colorToMove &= inverted_old_pos; */
/*   *bb_colorToMove |= new_pos; */

/*   /\* bb color to capture *\/ */
/*   *bb_colorToCapture &= inverted_old_pos; */
/* } */

void makeBoardMoveNonCapture(boardstate *bs, move *m, color side_to_move){
  int idx;
  bitboard inverted_old_pos = inverse[m->oldRow][m->oldCol];
  bitboard new_pos = pos[m->newRow][m->newCol];

  piece piece_to_move = getPieceType(bs, side_to_move, m->oldRow, m->oldCol);
  if (piece_to_move == NULL_PIECE){
    return;
  }

  if (side_to_move == WHITE){
    /* first do whiteLists */
    idx = 
      findBBLIndexOfPosition(&bs->whiteLists[piece_to_move], 
			     &pos[m->oldRow][m->oldCol]);
    bs->whiteLists[piece_to_move].bitboards[idx] = 0;
    bs->whiteLists[piece_to_move].bitboards[idx] |= new_pos;

    /* Now do whitePieces */
    bs->whitePieces[piece_to_move] &= inverted_old_pos;
    bs->whitePieces[piece_to_move] |= new_pos;

    /* now do all white */
    bs->allWhite &= inverted_old_pos;
    bs->allWhite |= new_pos;

  } else {
    /* first do blackLists */
    idx = 
      findBBLIndexOfPosition(&bs->blackLists[piece_to_move], 
			     &pos[m->oldRow][m->oldCol]);
    bs->blackLists[piece_to_move].bitboards[idx] = 0;
    bs->blackLists[piece_to_move].bitboards[idx] |= new_pos;

    /* Now do blackPieces */
    bs->blackPieces[piece_to_move] &= inverted_old_pos;
    bs->blackPieces[piece_to_move] |= new_pos;

    /* now do all black */
    bs->allBlack &= inverted_old_pos;
    bs->allBlack |= new_pos;

  }

  /* do full board */
  bs->fullBoard &= inverted_old_pos;
  bs->fullBoard |= new_pos;
}

void makeBoardMove(boardstate *bs, move *m, color side_to_move){
  /* @TODO - Ensure this function handles captures - done */

  if (isCapture(bs, m, side_to_move)){
    makeBoardMoveCapture(bs, m, side_to_move);
  } else {
    makeBoardMoveNonCapture(bs, m, side_to_move);
  }

  /* check to see if a pawn has made it to the opposite end, 
     and if it has, promote it */

  piece p = getPieceType(bs, side_to_move, m->newRow, m->newCol);
  if (p == PAWN){
    if (GET_PAWN_PROMOTION(m) == NULL_PIECE){
      return;
    }

    if (side_to_move == WHITE && m->newRow == 0){
      /* promote white pawn */
      bs_removePiece(bs, m->newRow, m->newCol);
      bs_placePiece(bs, WHITE, GET_PAWN_PROMOTION(m), m->newRow, m->newCol);
    } else if (side_to_move == BLACK && m->newRow == 7){
      /* promote black pawn */
      bs_removePiece(bs, m->newRow, m->newCol);
      bs_placePiece(bs, BLACK, GET_PAWN_PROMOTION(m), m->newRow, m->newCol);
    }
  }
}

/* void makeBoardMoveUsingBB(boardstate *bs, bitboard *move, color side_to_move){ */
/*   if (isCaptureUsingBB(bs, move, side_to_move)){ */
/*     makeBoardMoveCaptureUsingBB(bs, m, side_to_move); */
/*   } else { */
/*     makeBoardMoveNonCaptureUsingBB(bs, m, side_to_move); */
/*   } */
/* } */

boardstate * bs_deepCopy(boardstate *bs){
  int i;

  boardstate *bsReturn = (boardstate*)malloc(sizeof(boardstate));
  memcpy(bsReturn, bs, sizeof(boardstate));

  for (i = 0; i < PIECE_TYPES; i++){
    bbl_deepCopy(&bs->whiteLists[i], &bsReturn->whiteLists[i]);
    bbl_deepCopy(&bs->blackLists[i], &bsReturn->blackLists[i]);
  }
  return bsReturn;
}

void bsShallowFree(boardstate *bs){
  int i;
  for (i = 0; i < 6; i++){
    bblShallowFree(&bs->whiteLists[i]);
    bblShallowFree(&bs->blackLists[i]);
  }
}

int bsEquals(boardstate *bs1, boardstate *bs2){
  int i;
  for (i = 0; i < 6; i++){
    if (bs1->whitePieces[i] != bs2->whitePieces[i]){
      return 0;
    }
    if (bs1->blackPieces[i] != bs2->blackPieces[i]){
      return 0;
    }
  }

  return 1;
}

void findMoveFromTo(boardstate *bsFrom, boardstate *bsTo, move *m, color c){
  int i, j;
  bitboard_list *bblCurListFrom, *bblCurListTo;
  position *posOld, *posNew;
  bitboard bbTemp;

  for (i = 0; i < 6; i++){
    bblCurListFrom = c == WHITE ? &bsFrom->whiteLists[i] : 
      &bsFrom->blackLists[i];
    bblCurListTo = c == WHITE ? &bsTo->whiteLists[i] :
      &bsTo->blackLists[i];

    /* if following condition is true, must be a pawn promotion */
    if ((bblCurListFrom->length != bblCurListTo->length) &&
	i != PAWN){
      if (c == WHITE){
	bbTemp = bsFrom->whitePieces[PAWN] ^ bsTo->whitePieces[PAWN];
	posOld = getPositionOfFilled(&bbTemp);
	bbTemp = bsFrom->whitePieces[i] ^ bsTo->whitePieces[i];
	posNew = getPositionOfFilled(&bbTemp);
      } else {
	bbTemp = bsFrom->blackPieces[PAWN] ^ bsTo->blackPieces[PAWN];
	posOld = getPositionOfFilled(&bbTemp);
	bbTemp = bsFrom->blackPieces[i] ^ bsTo->blackPieces[i];
	posNew = getPositionOfFilled(&bbTemp);
      }
      
      setMoveWithPromotion(m, P_ROW(posOld), P_COL(posOld),
			   P_ROW(posNew), P_COL(posNew), i);
    }

    /* because of pawn promotions, both bitboard lists might
       not be the same length */
    for (j = 0; j < bblCurListFrom->length && j < bblCurListTo->length; j++){
      if (bblCurListFrom->bitboards[j] != 
	  bblCurListTo->bitboards[j]){
	posOld = getPositionOfFilled(&bblCurListFrom->bitboards[j]);
	posNew = getPositionOfFilled(&bblCurListTo->bitboards[j]);
	setMove(m, P_ROW(posOld), P_COL(posOld),
		P_ROW(posNew), P_COL(posNew));
	return;
      }
    }
  }
}
