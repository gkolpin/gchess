#ifndef BITBOARD_H
#define BITBOARD_H

#include "position.h"

typedef unsigned long long int bitboard;

void bb_init();

void setEmptyBitboard(bitboard*);
void setFullBitboard(bitboard*);
void invertBitboard(bitboard*);

void printBitboard(bitboard*);

void setFilled(bitboard*, int row, int col);
void setFilledFast(bitboard*, int row, int col);
int isFilled(bitboard*, int row, int col);
int isFilledFast(bitboard*, int row, int col);

void setEmpty(bitboard*, int row, int col);
void setEmptyFast(bitboard*, int row, int col);

void fillRow(bitboard *bb, int row);
void fillRowWith(bitboard*, int, char);
void fillAllRowsWith(bitboard*, char);

unsigned char getRow(bitboard*, int);
void setRow(bitboard*, int, char);
char getCol(bitboard*, int);

void union_bb(bitboard *bb1, bitboard *bb2, bitboard *result);
void union_bbSet(bitboard *bb, int numBB, bitboard *result);

void intersect_bb(bitboard *bb1, bitboard *bb2, bitboard *result);

void xor_bb(bitboard *bb1, bitboard *bb2, bitboard *result);

void flipboard(bitboard*);
void rotateBoard90(bitboard*);
void rotateBoardNeg90(bitboard*);
void rotateBoard45(bitboard*);
void rotateBoardNeg45(bitboard*);

int getIndexOfFilled(bitboard *bb, int numBB, int row, int col);

position * getPositionOfFilled(bitboard*);

#endif
