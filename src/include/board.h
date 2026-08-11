#ifndef BOARD_H
#define BOARD_H

#include "types.h"

typedef struct {
  bitboard_size pieces[2][6];
  int side_to_move;
  int castle_rights;
  int en_passant_square;
  int half_move_count;
  int full_move_count;
} Board;

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define WHITE_KING 0x1
#define WHITE_QUEEN 0x2
#define WHITE_ROOK 0x4
#define WHITE_KNIGHT 0x8

#endif
