#include "board.h"
#include <stdbool.h>


#ifndef MOVEGEN_H
#define MOVEGEN_H

// // Define piece constants
// enum Piece {
//     EMPTY = 0,
//     W_PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
//     B_PAWN, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING
// };

// Define colors
#define WHITE 1
#define BLACK -1

bool is_valid_chess_coordinate(const char* coord);
bool get_board_indices(const char* coord, int* row, int* col);
int validate_move(char board[BOARD_SIZE][BOARD_SIZE], int src_row, int src_col, int dest_row, int dest_col, int turn);

#endif