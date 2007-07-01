#include "bitboard.h"
#include "bitboard_list.h"

#include <stdlib.h>
#include <string.h>

bitboard_list * create_bbl(){
  bitboard_list *bbl_return;
  bbl_return = (bitboard_list*)malloc(sizeof(bitboard_list));
  bbl_return->length = 0;
  bbl_return->bitboards = NULL;
  return bbl_return;
}

void initialize_bbl(bitboard_list *bbl){
  bbl->length = 0;
  bbl->bitboards = NULL;
}

void free_bbl(bitboard_list *bbl){
  if (bbl->bitboards != NULL){
    free(bbl->bitboards);
  }
  
  free(bbl);
}

void insert_bb(bitboard_list *bbl, bitboard *bb){
  /* @TODO - Make realloc increase by 2x instead of +1 */
  if (bbl->bitboards == NULL){
    bbl->bitboards = (bitboard*)malloc(sizeof(bitboard));
  }
  else {
    bbl->bitboards = (bitboard*)realloc(bbl->bitboards, sizeof(bitboard) * (bbl->length + 1));
  }

  bbl->bitboards[bbl->length] = *bb;
  bbl->length++;
}

void delete_bb_at(bitboard_list *bbl, int index){
  int i;
  for (i = index; i < bbl->length - 1; i++){
    bbl->bitboards[i] = bbl->bitboards[i + 1];
  }

  bbl->length--;
  if (bbl->length == 0){
    free(bbl->bitboards);
    bbl->bitboards = NULL;
  } else {
    bbl->bitboards = (bitboard*)realloc(bbl->bitboards, sizeof(bitboard) * bbl->length);
  }
}

void get_bitboard_list(bitboard *bb, bitboard_list *bbl){
  int row, col;
  bitboard bb_temp;

  /* Create new bbl */
  initialize_bbl(bbl);

  for (row = 0; row < 8; row++){
    for (col = 0; col < 8; col++){
      setEmptyBitboard(&bb_temp);
      if (isFilled(bb, row, col)){
	setFilled(&bb_temp, row, col);
	insert_bb(bbl, &bb_temp);
      }
    }
  }
}

bitboard_list * get_bitboard_list_pointer(bitboard *bb){
  bitboard_list * bblReturn = create_bbl();
  get_bitboard_list(bb, bblReturn);
  return bblReturn;
}

void insert_bbl_into(bitboard_list *receiver, bitboard_list *bbl){
  int i;
  
  for (i = 0; i < bbl->length; i++){
    insert_bb(receiver, &bbl->bitboards[i]);
  }
}

void union_bbl(bitboard_list *list1, bitboard_list *list2, bitboard_list *result){
  result->length = list1->length + list2->length;
  
  result->bitboards = (bitboard*)malloc(sizeof(bitboard) * result->length);
  
  memcpy(result->bitboards, list1->bitboards, sizeof(bitboard) * list1->length);
  memcpy(&result->bitboards[list1->length], list2->bitboards, 
	 sizeof(bitboard) * list2->length);
}

void bbl_deepCopy(bitboard_list *src, bitboard_list *dst){
  dst->length = src->length;
  dst->bitboards = (bitboard*)malloc(sizeof(bitboard) * dst->length);
  memcpy(dst->bitboards, src->bitboards, sizeof(bitboard) * src->length);
}

void bblShallowFree(bitboard_list *bbl){
  free(bbl->bitboards);
}

int bbl_GetIndexOf(bitboard_list *bbl, bitboard bb){
  int i;
  for (i = 0; i < bbl->length; i++){
    if (bbl->bitboards[i] == bb){
      return i;
    }
  }
  
  return -1;
}
