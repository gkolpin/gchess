#include <stdlib.h>

#include "boardstate.h"
#include "game_state.h"
#include "enumerate_moves.h"
#include "moves.h"
#include "bitboards.h"
#include "bitboard.h"
#include "bitboard_list.h"
#include "position.h"
#include "game_state_list.h"
#include "move.h"

void init_enumerations();

void enumerate_pawn_moves(game_state*, game_state_list*);
void enumerate_knight_moves(game_state*, game_state_list*);
void enumerate_rook_moves(game_state*, game_state_list*);
void enumerate_bishop_moves(game_state*, game_state_list*);
void enumerate_queen_moves(game_state*, game_state_list*);
void enumerate_king_moves(game_state*, game_state_list*);

void enumeratePawnPromotions(game_state_list*, game_state*, color,
			       int row, int col);

void init_white_pawn_enumerations();
void init_black_pawn_enumerations();
void init_knight_enumerations();
void init_rook_enumerations();
void init_bishop_enumerations();
//void init_queen_enumerations();
void init_king_enumerations();

extern bitboard pawn_moves[8][8];
extern bitboard pawn_captures[8][8];
extern bitboard knight_moves[8][8];
extern bitboard rook_row_moves[8][8][256];
extern bitboard rook_col_moves[8][8][256];
extern bitboard king_move_masks[8][8];

/* possible pawn moves from position of white */
bitboard_list white_pawn_enumerations[8][8];
bitboard_list white_pawn_captures_enumerations[8][8];
bitboard_list black_pawn_enumerations[8][8];
bitboard_list black_pawn_captures_enumerations[8][8];
bitboard_list knight_enumerations[8][8];
bitboard_list rook_row_enumerations[8][8][256];
bitboard_list rook_col_enumerations[8][8][256];
bitboard_list bishop_rot_45_enumerations[8][8][256];
bitboard_list bishop_rot_neg_45_enumerations[8][8][256];
bitboard_list king_enumerations[8][8];

void init_enumerations(){
  moves_init();

  init_white_pawn_enumerations();
  init_knight_enumerations();
  init_rook_enumerations();
  init_bishop_enumerations();
  init_king_enumerations();
}

/* includes diagonal captures */
void init_white_pawn_enumerations(){
  int row, col;

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      get_bitboard_list(&pawn_moves[row][col],
			&white_pawn_enumerations[row][col]);
      get_bitboard_list(&pawn_captures[row][col],
			&white_pawn_captures_enumerations[row][col]);
    }
  }
  
  init_black_pawn_enumerations();
}

void init_black_pawn_enumerations(){
  int row, col, i;
  bitboard_list *cur_white_list, *cur_black_list;
  bitboard temp_bb;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      /* first do non_captures */
      cur_white_list = &white_pawn_enumerations[row][col];
      cur_black_list = &black_pawn_enumerations[7 - row][col];
      initialize_bbl(cur_black_list);
      for (i = 0; i < cur_white_list->length; i++){
	temp_bb = cur_white_list->bitboards[i];
	flipboard(&temp_bb);
	insert_bb(cur_black_list, &temp_bb);
      }

      /* now do captures */
      cur_white_list = &white_pawn_captures_enumerations[row][col];
      cur_black_list = &black_pawn_captures_enumerations[7 - row][col];
      initialize_bbl(cur_black_list);
      for (i = 0; i < cur_white_list->length; i++){
	temp_bb = cur_white_list->bitboards[i];
	flipboard(&temp_bb);
	insert_bb(cur_black_list, &temp_bb);
      }
    }
  }
}

void init_knight_enumerations(){
  int row, col;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      get_bitboard_list(&knight_moves[row][col], 
			&knight_enumerations[row][col]);
    }
  }
}

/* Includes captures on ends of rows and columns */
void init_rook_enumerations(){
  int row, col;
  int row_or_col_descr;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      for (row_or_col_descr = 0; row_or_col_descr < 256; row_or_col_descr++){
	get_bitboard_list(&rook_row_moves[row][col][row_or_col_descr],
			  &rook_row_enumerations[row][col][row_or_col_descr]);
	get_bitboard_list(&rook_col_moves[row][col][row_or_col_descr],
			  &rook_col_enumerations[row][col][row_or_col_descr]);
      }
    }
  }
}

#define BISHOP_ROT_45_MOVES(ROW, COL, ROW_DESCR) \
                 (ROW < COL) ? \
                 rook_row_moves[8 + (ROW - COL)][COL][ROW_DESCR] & LOWER_RIGHT : \
                 rook_row_moves[(ROW - COL)][COL][ROW_DESCR] & UPPER_LEFT

#define BISHOP_ROT_NEG_45_MOVES(ROW, COL, ROW_DESCR)\
                 (ROW < (8 - COL)) ? \
                 rook_row_moves[(ROW + COL) % 8][COL][ROW_DESCR] & LOWER_LEFT : \
                 rook_row_moves[(ROW + COL) % 8][COL][ROW_DESCR] & UPPER_RIGHT


void init_bishop_enumerations(){
  int row, col;
  unsigned int row_or_col_descr;
  bitboard bbNegRot, bbPosRot;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      for (row_or_col_descr = 0; row_or_col_descr < 256; row_or_col_descr++){
	bbNegRot = BISHOP_ROT_NEG_45_MOVES(row, col, row_or_col_descr);
	bbPosRot = BISHOP_ROT_45_MOVES(row, col, row_or_col_descr);
	
	rotateBoard45(&bbNegRot);
	rotateBoardNeg45(&bbPosRot);

	get_bitboard_list(&bbNegRot,
			  &bishop_rot_neg_45_enumerations
			  [row][col][row_or_col_descr]);
	get_bitboard_list(&bbPosRot,
			  &bishop_rot_45_enumerations[row][col][row_or_col_descr]);
      }
    }
  }
}

void init_king_enumerations(){
  int row, col;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      get_bitboard_list(&king_move_masks[row][col],
			&king_enumerations[row][col]);
    }
  }
}

void enumeratePawnPromotions(game_state_list *gsl, game_state *gs, color c,
			     int row, int col){
  game_state *gsTemp, *gsTemp2;
  boardstate *curBoardstate;

  gsTemp = gs_deepCopy(gs);
  bs_removePiece(getBoardstate(gsTemp), row, col);

  piece curPiece;
  for (curPiece = KNIGHT; curPiece <= QUEEN; curPiece++){
    gsTemp2 = gs_deepCopy(gsTemp);
    curBoardstate = getBoardstate(gsTemp2);
    bs_placePiece(curBoardstate, c, curPiece, row, col);
    insert_gs(gsl, gsTemp2);
  }

  gsShallowFree(gsTemp);
  free(gsTemp);
}

void enumerate_pawn_moves(game_state *gs, game_state_list *gslReturn){
  int i, j;
  game_state *gsTemp;
  bitboard *full_board;
  //bitboard *bbMove[2];
  move m;

  bitboard_list (*potential_pawn_moves)[8][8],
    (*potential_pawn_captures)[8][8];
  potential_pawn_moves = getPlayerToMove(gs) == WHITE ?
    &white_pawn_enumerations : &black_pawn_enumerations;
  potential_pawn_captures = getPlayerToMove(gs) == WHITE ?
    &white_pawn_captures_enumerations : &black_pawn_captures_enumerations;
  position *posTemp, *posTemp2;

  boardstate *bs = getBoardstate(gs);
  
  full_board = getFullBoard(bs);

  bitboard *opposing_pieces = getPlayerToMove(gs) == WHITE ?
    getAllBlack(bs) : getAllWhite(bs);

  bitboard_list *cur_pawn_positions = getPlayerToMove(gs) == WHITE ? 
    &bs->whiteLists[PAWN] :
    &bs->blackLists[PAWN];

  int isBlocked;

  bitboard_list *cur_pawn_moves;
  for (i = 0; i < cur_pawn_positions->length; i++){
    posTemp = getPositionOfFilled(&cur_pawn_positions->bitboards[i]);

    if (P_ROW(posTemp) == 6 && getPlayerToMove(gs) == WHITE){
      isBlocked = 1;
      if (!(*full_board & pos[P_ROW(posTemp) - 1][P_COL(posTemp)])){
	m = m_set_all(m, P_ROW(posTemp), P_COL(posTemp),
		      P_ROW(posTemp) - 1, P_COL(posTemp), NULL_PIECE, NULL_PIECE);
	gsTemp = gs_deepCopy(gs);
	makeMove(gsTemp, m);
	insert_gs(gslReturn, gsTemp);
	isBlocked = 0;
      }
      if (!(*full_board & pos[P_ROW(posTemp) - 2][P_COL(posTemp)]) && 
	  !isBlocked){
	m = m_set_all(m, P_ROW(posTemp), P_COL(posTemp),
		      P_ROW(posTemp) - 2, P_COL(posTemp), NULL_PIECE, NULL_PIECE);
	gsTemp = gs_deepCopy(gs);
	makeMove(gsTemp, m);
	insert_gs(gslReturn, gsTemp);
      }
    } else if (P_ROW(posTemp) != 6 && getPlayerToMove(gs) == WHITE){
      if (!(*full_board & pos[P_ROW(posTemp) - 1][P_COL(posTemp)])){
	m = m_set_all(m, P_ROW(posTemp), P_COL(posTemp),
		      P_ROW(posTemp) - 1, P_COL(posTemp), NULL_PIECE, NULL_PIECE);
	gsTemp = gs_deepCopy(gs);
	makeMove(gsTemp, m);
	if (m_get_nrow(m) == 0){
	  enumeratePawnPromotions(gslReturn, gsTemp, getPlayerToMove(gs),
				  m_get_nrow(m), m_get_ncol(m));
	  gsShallowFree(gsTemp);
	  free(gsTemp);
	} else {
	  insert_gs(gslReturn, gsTemp);
	}
      }      
    } else if (P_ROW(posTemp) == 1 && getPlayerToMove(gs) == BLACK){
      isBlocked = 1;
      if (!(*full_board & pos[P_ROW(posTemp) + 1][P_COL(posTemp)])){
	m = m_set_all(m, P_ROW(posTemp), P_COL(posTemp),
		      P_ROW(posTemp) + 1, P_COL(posTemp), NULL_PIECE, NULL_PIECE);
	gsTemp = gs_deepCopy(gs);
	makeMove(gsTemp, m);
	insert_gs(gslReturn, gsTemp);
	isBlocked = 0;
      }
      if (!(*full_board & pos[P_ROW(posTemp) + 2][P_COL(posTemp)]) &&
	  !isBlocked){
	m = m_set_all(m, P_ROW(posTemp), P_COL(posTemp),
		      P_ROW(posTemp) + 2, P_COL(posTemp), NULL_PIECE, NULL_PIECE);
	gsTemp = gs_deepCopy(gs);
	makeMove(gsTemp, m);
	insert_gs(gslReturn, gsTemp);
      }
    } else if (P_ROW(posTemp) != 1 && getPlayerToMove(gs) == BLACK){
      if (!(*full_board & pos[P_ROW(posTemp) + 1][P_COL(posTemp)])){
	m = m_set_all(m, P_ROW(posTemp), P_COL(posTemp),
		      P_ROW(posTemp) + 1, P_COL(posTemp), NULL_PIECE, NULL_PIECE);
	gsTemp = gs_deepCopy(gs);
	makeMove(gsTemp, m);
	if (m_get_nrow(m) == 7){
	  enumeratePawnPromotions(gslReturn, gsTemp, getPlayerToMove(gs),
				  m_get_nrow(m), m_get_ncol(m));
	  gsShallowFree(gsTemp);
	  free(gsTemp);
	} else {
	  insert_gs(gslReturn, gsTemp);
	}
      }
    }

    cur_pawn_moves = &potential_pawn_captures[0][posTemp->row][posTemp->col];
    for (j = 0; j < cur_pawn_moves->length; j++){
      if (*opposing_pieces & cur_pawn_moves->bitboards[j]){
	/* a capture is possible, record it! */
	gsTemp = gs_deepCopy(gs);
	posTemp2 = getPositionOfFilled(&cur_pawn_moves->bitboards[j]);
	m = m_set_all(m, P_ROW(posTemp), P_COL(posTemp),
		      P_ROW(posTemp2), P_COL(posTemp2), NULL_PIECE, NULL_PIECE);
	makeMove(gsTemp, m);
	if ((getPlayerToMove(gs) == WHITE && m_get_nrow(m) == 0) ||
	    (getPlayerToMove(gs) == BLACK && m_get_nrow(m) == 7)){
	  enumeratePawnPromotions(gslReturn, gsTemp, getPlayerToMove(gs), 
				  m_get_nrow(m), m_get_ncol(m));
	  gsShallowFree(gsTemp);
	  free(gsTemp);
	} else {
	  insert_gs(gslReturn, gsTemp);
	}
      }
    }
  }
}

void enumerate_knight_moves(game_state *gs, game_state_list *gslReturn){
  boardstate *bs = getBoardstate(gs);
  bitboard *curPos;
  bitboard_list *curPotentialMoves;
  position *posTemp1, *posTemp2;
  bitboard *friendly_pieces = getPlayerToMove(gs) == WHITE ?
    getAllWhite(bs) : getAllBlack(bs);
  game_state *gsTemp;
  move m;
  int i, j;

  /* get correct color's knight positions */
  bitboard_list *knight_pos = getPlayerToMove(gs) == WHITE ? 
    &bs->whiteLists[KNIGHT] :
    &bs->blackLists[KNIGHT];

  /* loop through bitboard_list of knight positions */
  for (i = 0; i < knight_pos->length; i++){
    curPos = &knight_pos->bitboards[i];
    posTemp1 = getPositionOfFilled(curPos);
    curPotentialMoves = &knight_enumerations[P_ROW(posTemp1)][P_COL(posTemp1)];

    /* nested loop of possible moves from current location */
    for (j = 0; j < curPotentialMoves->length; j++){
      /* if knight might hit friendly piece, then no move is possible */
      /* otherwise we can make the move, store it in the gslReturn */
      if (!(curPotentialMoves->bitboards[j] & *friendly_pieces)){
	gsTemp = gs_deepCopy(gs);
	posTemp2 = getPositionOfFilled(&curPotentialMoves->bitboards[j]);
	m = m_set_all(m, P_ROW(posTemp1), P_COL(posTemp1),
		      P_ROW(posTemp2), P_COL(posTemp2), NULL_PIECE, NULL_PIECE);
	makeMove(gsTemp, m);
	insert_gs(gslReturn, gsTemp);
      }
    }
  }
}

void enumerate_single_rook_moves(bitboard *curPos, game_state_list *toFill,
				 bitboard *fullBoard, bitboard *friendly_pieces,
				 game_state *gs){

  int j;
  bitboard_list *curRowPotentialMoves, *curColPotentialMoves;
  game_state *gsTemp;
  position *posTemp1, *posTemp2;
  move m;
  unsigned char rowDescr, colDescr;

  posTemp1 = getPositionOfFilled(curPos);

  rowDescr = getRow(fullBoard, P_ROW(posTemp1));
  colDescr = getCol(fullBoard, P_COL(posTemp1));
  
  curRowPotentialMoves = &rook_row_enumerations[P_ROW(posTemp1)][P_COL(posTemp1)]
    [rowDescr];
  curColPotentialMoves = &rook_col_enumerations[P_ROW(posTemp1)][P_COL(posTemp1)]
    [colDescr];

  /* row enumerations */
  for (j = 0; j < curRowPotentialMoves->length; j++){
    if (!(curRowPotentialMoves->bitboards[j] & *friendly_pieces)){
      gsTemp = gs_deepCopy(gs);
      posTemp2 = getPositionOfFilled(&curRowPotentialMoves->bitboards[j]);
      m = m_set_all(m, P_ROW(posTemp1), P_COL(posTemp1),
		    P_ROW(posTemp2), P_COL(posTemp2), NULL_PIECE, NULL_PIECE);
      makeMove(gsTemp, m);
      insert_gs(toFill, gsTemp);
    }
  }
  
  /* col enumerations */
  for (j = 0; j < curColPotentialMoves->length; j++){
    if (!(curColPotentialMoves->bitboards[j] & *friendly_pieces)){
      gsTemp = gs_deepCopy(gs);
      posTemp2 = getPositionOfFilled(&curColPotentialMoves->bitboards[j]);
      m = m_set_all(m, P_ROW(posTemp1), P_COL(posTemp1),
		    P_ROW(posTemp2), P_COL(posTemp2), NULL_PIECE, NULL_PIECE);
      makeMove(gsTemp, m);
      insert_gs(toFill, gsTemp);
    }
  }  
}

void enumerate_rook_moves(game_state *gs, game_state_list *gslReturn){
  boardstate *bs = getBoardstate(gs);
  bitboard *fullBoard = getFullBoard(bs);
  int i;
  bitboard *curPos;
  bitboard *friendly_pieces = getPlayerToMove(gs) == WHITE ?
    getAllWhite(bs) : getAllBlack(bs);

  /* get correct color's rook positions */
  bitboard_list *rook_pos = getPlayerToMove(gs) == WHITE ?
    &bs->whiteLists[ROOK] :
    &bs->blackLists[ROOK];
  
  /* loop through bitboard_list of rook positions */
  for (i = 0; i < rook_pos->length; i++){
    curPos = &rook_pos->bitboards[i];
    enumerate_single_rook_moves(curPos, gslReturn, fullBoard, friendly_pieces,
			       gs);
  }
}

void enumerate_single_bishop_moves(bitboard *curPos, game_state_list *toFill,
				   bitboard *fullBoard, bitboard *friendly_pieces,
				   bitboard *fullBoardPosRot,
				   bitboard *fullBoardNegRot,
				   game_state *gs){

  position *posTemp1, *posTemp2;
  bitboard_list *curPosDiagPotentialMoves, *curNegDiagPotentialMoves;
  unsigned char posRowDescr, negRowDescr;
  int j;
  game_state *gsTemp;
  move m;

  posTemp1 = getPositionOfFilled(curPos);
  
  int rotRowTemp;

  posRowDescr = getRow(fullBoardPosRot, (P_ROW(posTemp1) + P_COL(posTemp1)) % 8);

  rotRowTemp = P_ROW(posTemp1) < P_COL(posTemp1) ? 
    8 + (P_ROW(posTemp1) - P_COL(posTemp1)) : P_ROW(posTemp1) - P_COL(posTemp1);
  
  negRowDescr = getRow(fullBoardNegRot, rotRowTemp);
  
  curPosDiagPotentialMoves = &bishop_rot_neg_45_enumerations[P_ROW(posTemp1)]
    [P_COL(posTemp1)][posRowDescr];
  curNegDiagPotentialMoves = &bishop_rot_45_enumerations[P_ROW(posTemp1)]
    [P_COL(posTemp1)][negRowDescr];
  
  /* nested loop of possible moves from current location */
  
  /* posRot enumerations */
  for (j = 0; j < curPosDiagPotentialMoves->length; j++){
    if (!(curPosDiagPotentialMoves->bitboards[j] & *friendly_pieces)){
      gsTemp = gs_deepCopy(gs);
      posTemp2 = getPositionOfFilled(&curPosDiagPotentialMoves->bitboards[j]);
      m = m_set_all(m, P_ROW(posTemp1), P_COL(posTemp1),
		    P_ROW(posTemp2), P_COL(posTemp2), NULL_PIECE, NULL_PIECE);
      makeMove(gsTemp, m);
      insert_gs(toFill, gsTemp);
    }
  }
  
  /* negRot enumerations */
  for (j = 0; j < curNegDiagPotentialMoves->length; j++){
    if (!(curNegDiagPotentialMoves->bitboards[j] & *friendly_pieces)){
      gsTemp = gs_deepCopy(gs);
      posTemp2 = getPositionOfFilled(&curNegDiagPotentialMoves->bitboards[j]);
      m = m_set_all(m, P_ROW(posTemp1), P_COL(posTemp1),
		    P_ROW(posTemp2), P_COL(posTemp2), NULL_PIECE, NULL_PIECE);
      makeMove(gsTemp, m);
      insert_gs(toFill, gsTemp);
    }
  }  
}

void enumerate_bishop_moves(game_state *gs, game_state_list *gslReturn){
  boardstate *bs = getBoardstate(gs);
  bitboard *fullBoard = getFullBoard(bs);
  bitboard fullBoardTemp, fullBoardTemp2;
  int i;
  bitboard *curPos;
  bitboard *friendly_pieces = getPlayerToMove(gs) == WHITE ?
    getAllWhite(bs) : getAllBlack(bs);

  /* get correct color's bishop positions */
  bitboard_list *bishop_pos = getPlayerToMove(gs) == WHITE ?
    &bs->whiteLists[BISHOP] :
    &bs->blackLists[BISHOP];

  fullBoardTemp = *fullBoard;
  fullBoardTemp2 = *fullBoard;

  rotateBoardNeg45(&fullBoardTemp);
  rotateBoard45(&fullBoardTemp2);

  /* loop through bitboard_list of bishop positions */
  for (i = 0; i < bishop_pos->length; i++){
    curPos = &bishop_pos->bitboards[i];
    
    enumerate_single_bishop_moves(curPos, gslReturn,
				  fullBoard, friendly_pieces,
				  &fullBoardTemp,
				  &fullBoardTemp2,
				  gs);
  }
}

void enumerate_queen_moves(game_state *gs, game_state_list *gslReturn){
  boardstate *bs = getBoardstate(gs);
  bitboard *friendly_pieces = getPlayerToMove(gs) == WHITE ?
    getAllWhite(bs) : getAllBlack(bs);
  int i;
  bitboard *curPos;
  bitboard *fullBoard = getFullBoard(bs);
  bitboard fullBoardTemp, fullBoardTemp2;

  /* get correct color's queen position(s) */
  bitboard_list *queen_pos = getPlayerToMove(gs) == WHITE ?
    &bs->whiteLists[QUEEN] :
    &bs->blackLists[QUEEN];

  fullBoardTemp = *fullBoard;
  fullBoardTemp2 = *fullBoard;
  
  rotateBoardNeg45(&fullBoardTemp);
  rotateBoard45(&fullBoardTemp2);


  /* loop through bitboard_list of queen positions */
  for (i = 0; i < queen_pos->length; i++){
    curPos = &queen_pos->bitboards[i];
    
    /* queen moves are just a combination of rook and bishop moves */

    enumerate_single_rook_moves(curPos, gslReturn, fullBoard, friendly_pieces,
				gs);

    enumerate_single_bishop_moves(curPos, gslReturn,
				  fullBoard, friendly_pieces,
				  &fullBoardTemp,
				  &fullBoardTemp2,
				  gs);
  }
}

void enumerate_king_moves(game_state *gs, game_state_list *gslReturn){
  boardstate *bs = getBoardstate(gs);
  int i;
  bitboard *curPos;
  position *posTemp1, *posTemp2;
  bitboard_list *curPotentialMoves;
  bitboard *friendly_pieces = getPlayerToMove(gs) == WHITE ?
    getAllWhite(bs) : getAllBlack(bs);
  game_state *gsTemp;
  move m;

  /* get correct color's king position */
  bitboard_list *king_pos = getPlayerToMove(gs) == WHITE ?
    &bs->whiteLists[KING] :
    &bs->blackLists[KING];

  /* there's only ever one king, so retrieve it's position */
  curPos = &king_pos->bitboards[0];
  posTemp1 = getPositionOfFilled(curPos);
  curPotentialMoves = &king_enumerations[P_ROW(posTemp1)][P_COL(posTemp1)];

  /* loop through possible moves */
  for (i = 0; i < curPotentialMoves->length; i++){
    if (!(curPotentialMoves->bitboards[i] & *friendly_pieces)){
      gsTemp = gs_deepCopy(gs);
      posTemp2 = getPositionOfFilled(&curPotentialMoves->bitboards[i]);
      m = m_set_all(m, P_ROW(posTemp1), P_COL(posTemp1),
		    P_ROW(posTemp2), P_COL(posTemp2), NULL_PIECE, NULL_PIECE);
      makeMove(gsTemp, m);
      insert_gs(gslReturn, gsTemp);
    }
  }
}

game_state_list * enumerate_moves(game_state *gs, int removeChecks){
  game_state_list *gslReturn = create_gsl();

  enumerate_pawn_moves(gs, gslReturn);
  enumerate_knight_moves(gs, gslReturn);
  enumerate_rook_moves(gs, gslReturn);
  enumerate_bishop_moves(gs, gslReturn);
  enumerate_queen_moves(gs, gslReturn);
  enumerate_king_moves(gs, gslReturn);

  /* Determine if king is in check, and if so, eliminate moves
     that don't get the king out of check. */
  int i;

  if (removeChecks){
    
    for (i = 0; i < gslReturn->length; i++){
      if (isKingInCheck(gslReturn->game_states[i], 
			getPlayerToMove(gs))){
	delete_gs(gslReturn, i);
	i--;
      }
    }
  }

  return gslReturn;
}
