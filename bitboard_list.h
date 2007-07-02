#ifndef BITBOARD_LIST_H
#define BITBOARD_LIST_H

typedef struct {
  bitboard * bitboards;
  int length;
  /* length allocated */
  int l_alloc;
} bitboard_list;

#define BBL_LENGTH(bb) bb->length
#define BBL_BB_AT(bb, n) bb->bitboards[n]

bitboard_list * create_bbl();
void initialize_bbl(bitboard_list*);
void free_bbl(bitboard_list*);
void insert_bb(bitboard_list*, bitboard*);
void delete_bb_at(bitboard_list*, int);
void get_bitboard_list(bitboard*, bitboard_list*);
bitboard_list * get_bitboard_list_pointer(bitboard*);
void insert_bbl_into(bitboard_list* receiver, bitboard_list*);
void union_bbl(bitboard_list*, bitboard_list*, bitboard_list *result);
void bbl_deepCopy(bitboard_list *src, bitboard_list *dst);
void bblShallowFree(bitboard_list*);
int bbl_GetIndexOf(bitboard_list*, bitboard);

#endif
