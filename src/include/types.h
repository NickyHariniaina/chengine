#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

typedef enum { WHITE, BLACK } Color;

typedef enum { KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN } Piece;

typedef uint64_t bitboard_size;

#endif
