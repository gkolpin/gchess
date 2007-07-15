#ifndef MOVE_H
#define MOVE_H

#include "piece.h"

#include "sys/types.h"

/* A move is a 32 bit unsigned int - the layout of the structure
   is as follows:

   bits:  0 - 2: oldRow
          3 - 5: oldCol
          6 - 8: newRow
          9 - 11 newCol
          12 - 14: pawnPromotion
          15 - 17: capturedPiece 
*/
typedef uint32_t move;

#define FIELD_MASK 0x7

#define OROW_MASK 0x7

#define OCOL_MASK 0x38

#define NROW_MASK 0x1C0

#define NCOL_MASK 0xE00

#define PP_MASK 0x7000

#define CP_MASK 0x38000

#define m_get_orow(move) (move & FIELD_MASK)

#define m_get_ocol(move) ((move >> 3) & FIELD_MASK)

#define m_get_nrow(move) ((move >> 6) & FIELD_MASK)

#define m_get_ncol(move) ((move >> 9) & FIELD_MASK)

#define m_get_pp(move) ((move >> 12) & FIELD_MASK)

#define m_get_cp(move) ((move >> 15) & FIELD_MASK)

#define m_set_orow(m, row) ((m & ~OROW_MASK) | (row & FIELD_MASK))

#define m_set_ocol(m, col) ((m & ~OCOL_MASK) | ((col & FIELD_MASK) << 3))

#define m_set_nrow(m, row) ((m & ~NROW_MASK) | ((row & FIELD_MASK) << 6))

#define m_set_ncol(m, col) ((m & ~NCOL_MASK) | ((col & FIELD_MASK) << 9))

#define m_set_pp(m, pp) ((m & ~PP_MASK) | ((pp & FIELD_MASK) << 12))

#define m_set_cp(m, cp) ((m & ~CP_MASK) | ((cp & FIELD_MASK) << 15))

#define m_set_all(m, orow, ocol, nrow, ncol, pp, cp) (m_set_orow(0, orow) | \
                                                     m_set_ocol(0, ocol) | \
                                                     m_set_nrow(0, nrow) | \
                                                     m_set_ncol(0, ncol) | \
                                                     m_set_pp(0, pp) | \
                                                     m_set_cp(0, cp))

#endif
