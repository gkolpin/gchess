#include "bitboard.h"
#include "bitboard_list.h"

#include <stdlib.h>
#include <string.h>

void resize_grow(bitboard_list*);
void resize_shrink(bitboard_list*);

void resize_grow(bitboard_list *bbl){
  /* grow by 2x */
  bbl->l_alloc <<= 1;
  bbl->bitboards = (bitboard*)realloc(bbl->bitboards, 
				      sizeof(bitboard) * bbl->l_alloc);
}

void resize_shrink(bitboard_list *bbl){
  /* shrink by 2x */
  bbl->l_alloc >>= 1;
  bbl->bitboards = (bitboard*)realloc(bbl->bitboards,
				      sizeof(bitboard) * bbl->l_alloc);
}

bitboard_list * create_bbl(){
  bitboard_list *bbl_return;
  bbl_return = (bitboard_list*)malloc(sizeof(bitboard_list));
  bbl_return->length = 0;
  bbl_return->l_alloc = 0;
  bbl_return->bitboards = NULL;
  return bbl_return;
}

void initialize_bbl(bitboard_list *bbl){
  bbl->length = 0;
  bbl->bitboards = NULL;
  bbl->l_alloc = 0;
}

void free_bbl(bitboard_list *bbl){
  if (bbl->bitboards != NULL){
    free(bbl->bitboards);
  }
  
  free(bbl);
}

void insert_bb(bitboard_list *bbl, bitboard *bb){

  if (bbl->l_alloc == 0){
    bbl->bitboards = (bitboard*)malloc(sizeof(bitboard));
    bbl->l_alloc = 1;
  } else if (bbl->length == bbl->l_alloc){
    resize_grow(bbl);
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
    bbl->l_alloc = 0;
    return;
  } 
  /* shrink if length is a quarter of the size */
  else if (bbl->length <= (bbl->l_alloc >> 2)){
    resize_shrink(bbl);
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
  result->l_alloc = list1->l_alloc + list2->l_alloc;
  
  result->bitboards = (bitboard*)malloc(sizeof(bitboard) * result->l_alloc);
  
  memcpy(result->bitboards, list1->bitboards, sizeof(bitboard) * list1->length);
  memcpy(&result->bitboards[list1->length], list2->bitboards, 
	 sizeof(bitboard) * list2->length);
}

void bbl_deepCopy(bitboard_list *src, bitboard_list *dst){
  dst->length = src->length;
  dst->l_alloc = src->l_alloc;
  dst->bitboards = (bitboard*)malloc(sizeof(bitboard) * dst->l_alloc);
  memcpy(dst->bitboards, src->bitboards, sizeof(bitboard) * src->length);
}

void bblShallowFree(bitboard_list *bbl){
  free(bbl->bitboards);
  bbl->l_alloc = 0;
  bbl->length = 0;
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
