#ifndef BOARD_STATE_H
#define BOARD_STATE_H

#include "bitboard.h"
#include "util.h"
#include "move.h"
#include "bitboard_list.h"
#include "piece.h"

typedef struct boardstate{

  /**int numWhitePawns, numWhiteBishops, numWhiteKnights, 
    numWhiteRooks, numWhiteQueens;

  int numBlackPawns, numBlackBishops, numBlackKnights, 
  numBlackRooks, numBlackQueens;*/

  bitboard_list whiteLists[6];
  bitboard_list blackLists[6];

  bitboard whitePieces[6];
  bitboard blackPieces[6];

  bitboard fullBoard;

  bitboard allWhite;
  bitboard allBlack;
  
} boardstate;

#define BS_KING_POS(bs, color) color == WHITE ? \
                               bs->whitePieces[KING] : \
                               bs->blackPieces[KING]

boardstate * createDefaultBoardstate();
boardstate * createEmptyBoardstate();
//void setDefaultBoardstate(boardstate*);

void bs_placePiece(boardstate*, color, piece, int row, int col);
void bs_removePiece(boardstate*, int row, int col);

piece getPieceType(boardstate*, color, int row, int col);
piece getWhitePieceType(boardstate*, int row, int col);
piece getBlackPieceType(boardstate*, int row, int col);

bitboard * getAllWhite(boardstate*);
bitboard * getAllBlack(boardstate*);
bitboard * getFullBoard(boardstate*);

bitboard_list * getBitboardLists(boardstate*, color);

bitboard * getPawns(boardstate*, color);

int bs_isSpaceFilled(boardstate*, int row, int col);

void printBoardstate(boardstate*);

// Assumes move is correct move
void makeBoardMove(boardstate*, move*, color);

void findMoveFromTo(boardstate *from, boardstate *to, move*, color);

/* the second argument is a 2-d array of bitboards. The first
 slot is the old piece location, the second is the new. */
void makeBoardMoveUsingBB(boardstate*, bitboard*, color);

boardstate * bs_deepCopy(boardstate*);
void bsShallowFree(boardstate*);

int bsEquals(boardstate*, boardstate*);

#endif
