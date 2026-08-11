#include "include/bitboard.h"
#include "include/types.h"
#include <stdint.h>

const uint8_t MAX_BOARD_SIZE = 8;

// Usage of population count here so we can count bit at 1 faster. I think it's
// kinda obvious
int count_bits(bitboard_size board) { return __builtin_popcountll(board); }

// The fact is that we count like 0000_0001 and have h -> a because that's how
// it work to be honest
// So doing 0x1 << 3 will resolve in going to the d file
int pop_least_significant_bit(bitboard_size *board) {
  int square = __builtin_ctzll(*board);
  *board &= *board - 0b00000001;
  return square;
}

void print_bitboard(bitboard_size board) {
  for (int rank = MAX_BOARD_SIZE - 1; rank >= 0; rank--) {
    for (int file = 0; file < MAX_BOARD_SIZE; file++) {
      int square = rank * MAX_BOARD_SIZE + file;
      printf("%d", ((board >> square) & 0b00000001));
    }
    printf("\n");
  }
  printf("\n");
}
