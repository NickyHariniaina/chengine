#include "include/board.h"
#include "include/bitboard.h"
#include "include/types.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int char_to_piece(char c) {
  switch (tolower((unsigned char)c)) {
  case 'p':
    return PAWN;
  case 'r':
    return ROOK;
  case 'n':
    return KNIGHT;
  case 'b':
    return BISHOP;
  case 'q':
    return QUEEN;
  case 'k':
    return KING;
  default:
    return -1;
  }
}

static int name_to_square(const char *name) {
  return (name[0] - 'a') + (name[1] - '1') * 8;
}

void reset_board(Board *board) {
  memset(board->pieces, 0, sizeof(board->pieces));
  board->side_to_move = WHITE;
  board->castle_rights = 0;
  board->en_passant_square = -1;
  board->half_move_count = 0;
  board->full_move_count = 1;
}

void parse_fen(const char *fen, Board *b) {
  reset_board(b);

  int rank = 7, file = 0;
  const char *c = fen;

  for (; *c && *c != ' '; c++) {
    if (*c == '/') {
      rank--;
      file = 0;
    } else if (*c >= '1' && *c <= '8') {
      file += *c - '0';
    } else {
      int color = isupper(*c) ? WHITE : BLACK;
      int piece = char_to_piece(*c);
      set_bit(b->pieces[color][piece], rank * 8 + file);
      file++;
    }
  }

  c++;
  if (*c == 'w')
    b->side_to_move = WHITE;
  else if (*c == 'b')
    b->side_to_move = BLACK;

  c += 2;
  b->castle_rights = 0;
  if (*c == '-') {
    c++;
  } else {
    for (; *c && *c != ' '; c++) {
      if (*c == 'K')
        b->castle_rights |= CASTLE_W_KING;
      else if (*c == 'Q')
        b->castle_rights |= CASTLE_W_QUEEN;
      else if (*c == 'k')
        b->castle_rights |= CASTLE_B_KING;
      else if (*c == 'q')
        b->castle_rights |= CASTLE_B_QUEEN;
    }
  }

  if (*c == ' ')
    c++;
  b->en_passant_square = -1;
  if (*c != '-')
    b->en_passant_square = name_to_square(c);
  c += 2;

  if (*c == ' ')
    c++;
  b->half_move_count = atoi(c);
  while (*c && *c != ' ')
    c++;
  if (*c == ' ')
    c++;
  b->full_move_count = atoi(c);
}

bitboard_size get_color_occurence(Board *board, Color color) {
  bitboard_size pawn_bitboard = board->pieces[color][PAWN];
  bitboard_size knight_bitboard = board->pieces[color][KNIGHT];
  bitboard_size bishop_bitboard = board->pieces[color][BISHOP];
  bitboard_size rook_bitboard = board->pieces[color][ROOK];
  bitboard_size queen_bitboard = board->pieces[color][QUEEN];
  bitboard_size king_bitboard = board->pieces[color][KING];

  return pawn_bitboard | knight_bitboard | bishop_bitboard | rook_bitboard |
         queen_bitboard | king_bitboard;
}

bitboard_size get_occurence(Board *board, Piece piece) {
  bitboard_size white_occurence = get_color_occurence(board, WHITE);
  bitboard_size black_occurence = get_color_occurence(board, BLACK);
  return white_occurence | black_occurence;
}

int get_king_square(Board *board, Color color) {
  return __builtin_ctzll(board->pieces[color][KING]);
}

void print_board(Board *board) {

  static const char piece_char[2][6] = {{'K', 'Q', 'R', 'N', 'B', 'P'},
                                        {'k', 'q', 'r', 'n', 'b', 'p'}};

  for (int rank = 7; rank >= 0; rank--) {
    printf("  +------------------------+\n");
    printf("  |");
    for (int file = 0; file < 8; file++) {
      int square = rank * 8 + file;
      char c = '.';
      for (int color = 0; color < 2; color++) {
        for (int piece = 0; piece < 6; piece++) {
          if (get_bit(board->pieces[color][piece], square)) {
            c = piece_char[color][piece];
          }
        }
      }
      printf("%c", c);
    }
    printf(" | %d\n", rank + 1);
  }
  printf("  +------------------------+\n");
}
