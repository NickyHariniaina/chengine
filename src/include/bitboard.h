#ifndef BITBOARD_H
#define BITBOARD_H

#include "types.h"
#include <stdint.h>

#define ONE_MASK (uint64_t)0x1
#define COL_A_MASK (uint64_t)0x101010101010101
#define COL_H_MASK (uint64_t)0x8080808080808080
#define RANK_1_MASK (uint64_t)0xff
#define RANK_8_MASK (uint64_t)0xff00000000000000

#define one_mask_shift_left(square) (ONE_MASK << (square))
#define set_bit(board, square) ((board) |= one_mask_shift_left(square))
#define get_bit(board, squar) ((board) & one_mask_shift_left(square))
#define clear_bit(board, square) ((board) &= one_mask_shift_left(square))

int count_bits(bitboard_size board);
int pop_least_significant_bit(bitboard_size *board);
void print_bitboard(bitboard_size board);

#endif
