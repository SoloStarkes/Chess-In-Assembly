#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 8
extern char board[BOARD_SIZE][BOARD_SIZE];
// White pieces
#define W_PAWN   'P'
#define W_KNIGHT 'N'
#define W_BISHOP 'B'
#define W_ROOK   'R'
#define W_QUEEN  'Q'
#define W_KING   'K'

// Black pieces
#define B_PAWN   'p'
#define B_KNIGHT 'n'
#define B_BISHOP 'b'
#define B_ROOK   'r'
#define B_QUEEN  'q'
#define B_KING   'k'

// Empty square
#define EMPTY    '.'

// Horizontal line
#define HLINE    "---------------\n"

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE]);
void display_board(char board[BOARD_SIZE][BOARD_SIZE], char* player1, char* player2);

#endif