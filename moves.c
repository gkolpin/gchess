#include "moves.h"
#include "move.h"
#include "bitboard.h"
#include "game_state.h"
#include "bitboards.h"
#include "enumerate_moves.h"
#include "game_state_list.h"

#define UNFRIENDLY 0
#define FRIENDLY 1

bitboard pawn_moves[8][8];
bitboard pawn_captures[8][8];
bitboard knight_moves[8][8];
bitboard rook_row_moves[8][8][256];
bitboard rook_col_moves[8][8][256];
//bitboard bishop_rot_45_moves[8][8][256];
//bitboard bishop_rot_neg_45_moves[8][8][256];
bitboard king_move_masks[8][8];
int initted = 0;
//void moves_init();
void initPawnMoves();
void initPawnCaptures();
void initKnightMoves();
void initRookMoves();
//void initBishopMoves();
void initKingMoveMasks();
void initRowMoves(bitboard[8][8][256]);
int isLegalPawnMove(game_state*, move*);
int isLegalKnightMove(game_state*, move*);
int isLegalRookMove(game_state*, move*);
int isLegalBishopMove(game_state*, move*);
int isLegalQueenMove(game_state*, move*);
int isLegalKingMove(game_state*, move*);

void moves_init(){
  initted = 1;
  
  initPawnMoves();
  initPawnCaptures();
  initKnightMoves();
  initRookMoves();
  //  initBishopMoves();
  initKingMoveMasks();
}

void initPawnCaptures(){
  int row;
  int col;
  bitboard *cur_bb;
  for (row = 0; row < 7; row++){
    for (col = 0; col < 8; col++){
      cur_bb = &pawn_captures[row][col];
      setEmptyBitboard(cur_bb);

      if (col == 0){
	setFilled(cur_bb, row - 1, col + 1);
	continue;
      }

      if (col == 7){
	setFilled(cur_bb, row - 1, col - 1);
	continue;
      }

      setFilled(cur_bb, row - 1, col - 1);
      setFilled(cur_bb, row - 1, col + 1);
    }
  }
}

void initPawnMoves(){
  int row;
  int col;
  bitboard *cur_bb;
  for (row = 0; row < 7; row++){
    for (col = 0; col < 8; col++){
      
      cur_bb = &pawn_moves[row][col];
      setEmptyBitboard(cur_bb);

      if (row == 6){
	setFilled(cur_bb, 5, col);
	setFilled(cur_bb, 4, col);
	continue;
      }

      setFilled(cur_bb, row - 1, col);

    }
  }
}
 
void initKnightMoves(){
  int row, col, i;
  int krow, kcol;

  bitboard *cur_bb;
  
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){

      setEmptyBitboard(&knight_moves[row][col]);
      
      for (i = 0; i < 8; i++){
	
	krow = row;
	kcol = col;

	switch(i){
	case 0: 
	  krow -= 2;
	  kcol += 1;
	  break;
	case 1:
	  krow -= 2;
	  kcol -= 1;
	  break;
	case 2:
	  krow += 2;
	  kcol += 1;
	  break;
	case 3:
	  krow += 2;
	  kcol -= 1;
	  break;
	case 4:
	  kcol -= 2;
	  krow += 1;
	  break;
	case 5:
	  kcol -= 2;
	  krow -= 1;
	  break;
	case 6:
	  kcol += 2;
	  krow += 1;
	  break;
	case 7:
	  kcol += 2;
	  krow -= 1;
	  break;
	}
	
	if (krow > 7 || krow < 0 || kcol > 7 || kcol < 0)
	  continue;
	
	setFilled(&knight_moves[row][col], krow, kcol);

      }

    }
  }
}

/* Assumes array bounds are [8][8][256]
   For row_array, final dimension passed is row description */
void initRowMoves(bitboard row_array[8][8][256]){
  //first initialize rook_row_moves - include captures on ends
  /* Each resulting bitboard has an extra bit set at the end
     of each row and column. This is to account for possible captures
     on the ends of the rows and columns. In order to correctly calculate
     the captures, we xor with the bitboard pieces of our own color,
     then intersect with the original (either rook_row_moves or
     rook_col_moves) bitboard. */

  int row, col, k, rowDescrInt;
  unsigned char rowDescr;
  bitboard *curBoard;
  int delete = 0;
  bitboard tempBoard;

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      for (rowDescr = 0, rowDescrInt = 0; 
	   rowDescrInt < 256; 
	   rowDescr++, rowDescrInt++){
      
	curBoard = &row_array[row][col][rowDescr];

	setEmptyBitboard(curBoard);

	fillRowWith(curBoard, row, (char)rowDescr);

	setEmpty(curBoard, row, col);

	//fill row backwards
	for (k = col - 1; k >= 0; k--){
	  if (isFilled(curBoard, row, k) && !delete){
	    delete = 1;
	    continue;
	  }
	  if (delete)
	    setEmpty(curBoard, row, k);
	  else
	    setFilled(curBoard, row, k);	
	}

	delete = 0;

	//fill row forwards
	for (k = col + 1; k < 8; k++){
	  if (isFilled(curBoard, row, k) && !delete){
	    delete = 1;
	    continue;
	  }
	  if (delete)
	    setEmpty(curBoard, row, k);
	  else
	    setFilled(curBoard, row, k);	
	}
      
	delete = 0;

#ifdef MOVES_ROOK_DEBUG

	printf("row: %d, col: %d\n", row, col);
	printBitboard(curBoard);
	printf("\n\n");

#endif

      }
    }
  }
}

void initRookMoves(){
  int row, col, k, rowDescrInt;
  bitboard *curBoard;
  int delete = 0;
  bitboard tempBoard;
  unsigned char rowDescr;

  /* First initialize rook_row_moves */
  initRowMoves(rook_row_moves);

  //initialize rook_col_moves - include captures on ends

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      for (rowDescr = 0, rowDescrInt = 0; 
	   rowDescrInt < 256; 
	   rowDescr++, rowDescrInt++){

	tempBoard = rook_row_moves[row][col][rowDescr];
      
/* 	printf("Before: \n"); */
/* 	printBitboard(&tempBoard); */

	rotateBoard90(&tempBoard);

/* 	printf("After: \n"); */
/* 	printBitboard(&tempBoard); */

	rook_col_moves[7 - col][row][rowDescr] = tempBoard;      

#ifdef ROOK_MOVE_DEBUG

	printf("row: %d, col: %d, descr: %d\n", 7 - col, row, rowDescr);
	printBitboard(&rook_col_moves[7 - col][row][rowDescr]);
	//printBitboard(&tempBoard);
	printf("\n\n");

#endif

      }
    }
  }

}

#define BISHOP_ROT_45_MOVES(ROW, COL, ROW_DESCR) \
                 (ROW < COL) ? \
                 rook_row_moves[(ROW - COL) % 8][COL][ROW_DESCR] & LOWER_RIGHT : \
                 rook_row_moves[(ROW - COL) % 8][COL][ROW_DESCR] & UPPER_LEFT

#define BISHOP_ROT_NEG_45_MOVES(ROW, COL, ROW_DESCR)\
                 (ROW < (8 - COL)) ? \
                 rook_row_moves[(ROW + COL) % 8][COL][ROW_DESCR] & LOWER_LEFT : \
                 rook_row_moves[(ROW + COL) % 8][COL][ROW_DESCR] & UPPER_RIGHT

void initKingMoveMasks(){
  /* We'll set up a square of ones around the king's position */

  int row, col;
  bitboard *cur_bb;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      cur_bb = &king_move_masks[row][col];

      setEmptyBitboard(cur_bb);

      /* upper left */
      if (row != 0 && col != 0){
	setFilled(cur_bb, row - 1, col - 1);
      }

      /* upper center */
      if (row != 0){
	setFilled(cur_bb, row - 1, col);
      }

      /* upper right */
      if (row != 0 && col != 7){
	setFilled(cur_bb, row - 1, col + 1);
      }

      /* left center */
      if (col != 0){
	setFilled(cur_bb, row, col - 1);
      }

      /* right center */
      if (col != 7){
	setFilled(cur_bb, row, col + 1);
      }

      /* lower right */
      if (row != 7 && col != 0){
	setFilled(cur_bb, row + 1, col - 1);
      }

      /* lower center */
      if (row != 7){
	setFilled(cur_bb, row + 1, col);
      }

      /* lower right */
      if (row != 7 && col != 7){
	setFilled(cur_bb, row + 1, col + 1);
      }
    }
  }
}

/*
void initBishopMoves(){}
*/

int isLegalPawnMove(game_state* gs, move* m){
  /**
   * @TODO: determine en passante moves,
   * precompute flipped bitboards
   */
  
  bitboard noncaptures;
  bitboard captures;
  
  bitboard possible_moves;
  bitboard temp;

  if (getPlayerToMove(gs) == WHITE){
    noncaptures = pawn_moves[m->oldRow][m->oldCol];
    captures = pawn_captures[m->oldRow][m->oldCol];
    
    intersect_bb(&captures, getAllBlack(getBoardstate(gs)), &possible_moves);
    
  }

  else{

    noncaptures = pawn_moves[7 - m->oldRow][m->oldCol];
    captures = pawn_captures[7 - m->oldRow][m->oldCol];

    flipboard(&noncaptures);
    flipboard(&captures);
    intersect_bb(&captures, getAllWhite(getBoardstate(gs)), &possible_moves);    

  }

  
  xor_bb(&noncaptures, getFullBoard(getBoardstate(gs)), &temp);
  
  intersect_bb(&noncaptures, &temp, &temp);
  
  union_bb(&temp, &possible_moves, &possible_moves);
  
  if (isFilled(&possible_moves, m->newRow, m->newCol))
    return 1;
  
  return 0;
}

int isLegalKnightMove(game_state* gs, move* m){
  bitboard possible_moves = knight_moves[m->oldRow][m->oldCol];
  bitboard temp;

  if (getPlayerToMove(gs) == WHITE){
    xor_bb(&possible_moves, getAllBlack(getBoardstate(gs)), &temp);
  }
  else{
    xor_bb(&possible_moves, getAllWhite(getBoardstate(gs)), &temp);
  }

  intersect_bb(&temp, &possible_moves, &possible_moves);

  if (isFilled(&possible_moves, m->newRow, m->newCol))
    return 1;

  return 0;
}

int isLegalRookMove(game_state *gs, move *m){
  unsigned char row_description = getRow(getFullBoard(getBoardstate(gs)), m->oldRow);
  unsigned char col_description = getCol(getFullBoard(getBoardstate(gs)), m->oldCol);

  bitboard possible_moves;
  bitboard temp;

  union_bb(&rook_row_moves[m->oldRow][m->oldCol][row_description],
	   &rook_col_moves[m->oldRow][m->oldCol][col_description], 
	   &possible_moves);

  /*printf("row: %d, col: %d, col descr: %hhu\n", m->oldRow, m->oldCol, col_description);
  printBitboard(&rook_row_moves[m->oldRow][m->oldCol][row_description]);
  printBitboard(&rook_col_moves[m->oldRow][m->oldCol][col_description]);
  printBitboard(&rook_col_moves[0][0][156]);*/

  /* Make sure that the captures on the row and column ends 
     are correct */

  if (getPlayerToMove(gs) == WHITE){
    xor_bb(&possible_moves, getAllWhite(getBoardstate(gs)), &temp);
  }
  else{
    xor_bb(&possible_moves, getAllBlack(getBoardstate(gs)), &temp);
  }

  intersect_bb(&temp, &possible_moves, &possible_moves);
  
  if (isFilled(&possible_moves, m->newRow, m->newCol))
    return 1;
  
  return 0;
}
 
int isLegalBishopMove(game_state *gs, move *m){
  unsigned char pos_diag_description;
  unsigned char neg_diag_description;

  bitboard temp_bb1, temp_bb2, possible_moves, temp;

  temp_bb1 = temp_bb2 = *getFullBoard(getBoardstate(gs));

  rotateBoard45(&temp_bb1);
  rotateBoardNeg45(&temp_bb2);

  neg_diag_description = getRow(&temp_bb1, (m->oldRow - m->oldCol) % 8);
  pos_diag_description = getRow(&temp_bb2, (m->oldRow + m->oldCol) % 8);

  temp_bb1 = BISHOP_ROT_45_MOVES(m->oldRow, m->oldCol, neg_diag_description);
  temp_bb2 = BISHOP_ROT_NEG_45_MOVES(m->oldRow, m->oldCol, pos_diag_description);

  /* Now rotate the positive diagonals positively and the 
     negative ones negatively so they are back to their original
     orientation. */
  rotateBoardNeg45(&temp_bb1);
  rotateBoard45(&temp_bb2);

  union_bb(&temp_bb1, &temp_bb2, &possible_moves);

  /* Below is the same as for the rook move once we have unioned
     the two bitboards together. */

  if (getPlayerToMove(gs) == WHITE){
    xor_bb(&possible_moves, getAllWhite(getBoardstate(gs)), &temp);
  }
  else{
    xor_bb(&possible_moves, getAllBlack(getBoardstate(gs)), &temp);
  }

  intersect_bb(&temp, &possible_moves, &possible_moves);

  if (isFilled(&possible_moves, m->newRow, m->newCol))
    return 1;
  
  return 0;
}

int isLegalQueenMove(game_state *gs, move *m){
  /* This should be easy, just or isLegalRook move and
     isLegalBishopMove */

  if (isLegalRookMove(gs, m) || isLegalBishopMove(gs, m)){
    return 1;
  }

  return 0;
}

int isLegalKingMove(game_state *gs, move *m){
  /* This is similar to the queen move except that we can
     move a maximum/minimum of one square */

  /* @TODO - make sure king can't move into check */

  if (isLegalQueenMove(gs, m) && isFilled(&king_move_masks[m->oldRow][m->oldCol],
					  m->newRow, m->newCol)){
    return 1;
  }

  return 0;
}
