#include <stdio.h>

#include "enumerate_moves.h"
#include "bitboard_list.h"
#include "bitboard.h"
#include "bitboards.h"

extern bitboard_list bishop_rot_45_enumerations[8][8][256];
extern bitboard_list bishop_rot_neg_45_enumerations[8][8][256];

extern bitboard_list rook_row_enumerations[8][8][256];
extern bitboard_list rook_col_enumerations[8][8][256];

extern bitboard_list king_enumerations[8][8];

void enumerate_pawn_moves(game_state*, game_state_list*);
void enumerate_knight_moves(game_state*, game_state_list*);
void enumerate_rook_moves(game_state*, game_state_list*);
void enumerate_bishop_moves(game_state*, game_state_list*);
void enumerate_queen_moves(game_state*, game_state_list*);
void enumerate_king_moves(game_state*, game_state_list*);

extern bitboard rook_row_moves[8][8][256];

#define BISHOP_ROT_45_MOVES(ROW, COL, ROW_DESCR) \
                 (ROW < COL) ? \
                 rook_row_moves[(ROW - COL) % 8][COL][ROW_DESCR] & LOWER_RIGHT : \
                 rook_row_moves[(ROW - COL) % 8][COL][ROW_DESCR] & UPPER_LEFT

#define BISHOP_ROT_NEG_45_MOVES(ROW, COL, ROW_DESCR)\
                 (ROW < (8 - COL)) ? \
                 rook_row_moves[(ROW + COL) % 8][COL][ROW_DESCR] & LOWER_LEFT : \
                 rook_row_moves[(ROW + COL) % 8][COL][ROW_DESCR] & UPPER_RIGHT


void init(){
  init_enumerations();
  bb_init();
}

void testBishop(){

  int row, col;
  unsigned int descr;
  int i;
  bitboard_list curList45, curListNeg45;
  bitboard toPrint = 0;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      for (descr = 0; descr < 256; descr++){
	curList45 = bishop_rot_45_enumerations[row][col][descr];
	curListNeg45 = bishop_rot_neg_45_enumerations[row][col][descr];
	
 	for (i = 0; i < curList45.length; i++){ 
 	  toPrint |= curList45.bitboards[i]; 
 	} 
	
	for (i = 0; i < curListNeg45.length; i++){ 
 	  toPrint |= curListNeg45.bitboards[i]; 
 	} 
	
	printf("%d %d\n", row, col);
	printBitboard(&toPrint);
	toPrint = 0;
      }
    }
  }
}

void testRook(){
  int row, col;
  int descr;
  int i;
  bitboard_list curRowList, curColList;
  bitboard toPrint = 0;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      for (descr = 0; descr < 256; descr++){
	curRowList = rook_row_enumerations[row][col][descr];
	curColList = rook_col_enumerations[row][col][descr];

	for (i = 0; i < curRowList.length; i++){
	  toPrint |= curRowList.bitboards[i];
	}

	for (i = 0; i < curColList.length; i++){
	  toPrint |= curColList.bitboards[i];
	}

	printf("\n\n%d %d\n", row, col);
	printBitboard(&toPrint);
	toPrint = 0;
      }
    }
  }
}

void testKing(){
  int row, col;
  int i;
  bitboard toPrint = 0;
  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      toPrint = 0;
      for (i = 0; i < king_enumerations[row][col].length; i++){
	toPrint |= king_enumerations[row][col].bitboards[i];
      }
      printBitboard(&toPrint);
    }
  }
}

void testEnumeratePawnMoves(){
  game_state_list *gsl = create_gsl();

  game_state *gs = createGamestate(createDefaultBoardstate(), BLACK);
  
  enumerate_pawn_moves(gs, gsl);
  
  int i;

  for (i = 0; i < gsl->length; i++){
    printf("\n\n");
    printBoardstate(getBoardstate(&gsl->game_states[i]));
  }
}

void testEnumerateKnightMoves(){
  game_state_list *gsl = create_gsl();

  game_state *gs = createGamestate(createDefaultBoardstate(), WHITE);
  
  enumerate_knight_moves(gs, gsl);
  
  int i;

  for (i = 0; i < gsl->length; i++){
    printf("\n\n");
    printBoardstate(getBoardstate(&gsl->game_states[i]));
  }
}

void testEnumerateRookMoves(){
  game_state_list *gsl = create_gsl();

  game_state *gs = createGamestate(createDefaultBoardstate(), WHITE);
  
  move m1, m2;
  setMove(&m1, 6, 0, 4, 0);
  setMove(&m2, 1, 0, 2, 0);

  //makeMove(gs, &m2);
  //makeMove(gs, &m1);

  enumerate_rook_moves(gs, gsl);
  
  int i;

  for (i = 0; i < gsl->length; i++){
    printf("\n\n");
    printBoardstate(getBoardstate(&gsl->game_states[i]));
  }
}

void testEnumerateBishopMoves(){
  game_state_list *gsl = create_gsl();

  game_state *gs = createGamestate(createDefaultBoardstate(), WHITE);
  
  move m1, m2, m3, m4;
  setMove(&m1, 6, 1, 4, 1);
  setMove(&m2, 1, 0, 2, 0);
  setMove(&m3, 6, 3, 4, 3);
  setMove(&m4, 1, 1, 2, 1);

  makeMove(gs, &m1);
  makeMove(gs, &m2);
  makeMove(gs, &m3);
  makeMove(gs, &m4);

  enumerate_bishop_moves(gs, gsl);
  
  int i;

  for (i = 0; i < gsl->length; i++){
    printf("\n\n");
    printBoardstate(getBoardstate(&gsl->game_states[i]));
  }
}

void testEnumerateQueenMoves(){
  game_state_list *gsl = create_gsl();

  game_state *gs = createGamestate(createDefaultBoardstate(), WHITE);
  
  move m1, m2, m3, m4;
  setMove(&m1, 6, 1, 4, 1);
  setMove(&m2, 1, 0, 2, 0);
  setMove(&m3, 6, 3, 4, 3);
  setMove(&m4, 1, 1, 2, 1);

  makeMove(gs, &m1);
  makeMove(gs, &m2);
  makeMove(gs, &m3);
  makeMove(gs, &m4);
  
  enumerate_queen_moves(gs, gsl);
  
  int i;

  for (i = 0; i < gsl->length; i++){
    printf("\n\n");
    printBoardstate(getBoardstate(&gsl->game_states[i]));
    printBitboard(&(getBoardstate(&gsl->game_states[i]))->whiteLists[QUEEN].bitboards[0]);
  }
}

void testEnumerateKingMoves(){
  game_state_list *gsl = create_gsl();
  game_state *gs = createGamestate(createDefaultBoardstate(), WHITE);
  
  move m1, m2, m3, m4;
  setMove(&m1, 6, 1, 4, 1);
  setMove(&m2, 1, 0, 2, 0);
  setMove(&m3, 6, 3, 4, 3);
  setMove(&m4, 1, 1, 2, 1);

  makeMove(gs, &m1);
  makeMove(gs, &m2);
  makeMove(gs, &m3);
  makeMove(gs, &m4);

  enumerate_king_moves(gs, gsl);
  
  int i;

  for (i = 0; i < gsl->length; i++){
    printf("\n\n");
    printBoardstate(getBoardstate(&gsl->game_states[i]));
  }
}

void testEnumeratePawnPromotions(){
  boardstate *bs = createEmptyBoardstate();
  game_state_list *gsl = create_gsl();

  /* place kings */
  bs_placePiece(bs, WHITE, KING, 7, 7);
  bs_placePiece(bs, BLACK, KING, 1, 1);

  /* place white pawn */
  bs_placePiece(bs, WHITE, PAWN, 1, 5);

  game_state *gs = createGamestate(bs, WHITE);

  enumerate_pawn_moves(gs, gsl);
  int i;
  for (i = 0; i < gsl->length; i++){
    printf("\n\n");
    printBoardstate(getBoardstate(&gsl->game_states[i]));
  }
}

int main(){
  init();

  //testBishop();
  //testRook();
  //testKing();
  //testEnumeratePawnMoves();
  //testEnumerateKnightMoves();
  //testEnumerateRookMoves();
  //testEnumerateBishopMoves();
  //testEnumerateQueenMoves();
  //testEnumerateKingMoves();
  testEnumeratePawnPromotions();
}
