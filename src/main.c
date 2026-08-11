#include "include/board.h"
#include <stdlib.h>

int main(void) {
  Board board;
  parse_fen(START_FEN, &board);
  print_board(&board);
  return EXIT_SUCCESS;
}
