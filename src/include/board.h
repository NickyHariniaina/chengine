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

#define CASTLE_W_QUEEN 0b00000001
#define CASTLE_B_QUEEN 0b00000010
#define CASTLE_B_KING 0b00000100
#define CASTLE_W_KING 0b00001000

void reset_board(Board *board);
void parse_fen(const char *fen, Board *b);
void print_board(Board *board);

#endif
