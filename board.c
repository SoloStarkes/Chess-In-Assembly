#include <stdio.h>
#include "board.h"

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Place empty squares
    for (int i = 2; i < 6; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = EMPTY;

    // Place white pieces
    char white_back_rank[] = {W_ROOK, W_KNIGHT, W_BISHOP, W_QUEEN, W_KING, W_BISHOP, W_KNIGHT, W_ROOK};
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[7][j] = white_back_rank[j];
        board[6][j] = W_PAWN;
    }

    // Place black pieces
    char black_back_rank[] = {B_ROOK, B_KNIGHT, B_BISHOP, B_QUEEN, B_KING, B_BISHOP, B_KNIGHT, B_ROOK};
    for (int j = 0; j < BOARD_SIZE; j++) {
        board[0][j] = black_back_rank[j];
        board[1][j] = B_PAWN;
    }
}

void display_board(char board[BOARD_SIZE][BOARD_SIZE], char* player1, char* player2) {
    printf("  %s(B)\n  %s", player2, HLINE);
    printf("  a b c d e f g h\n  %s", HLINE);
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d|", BOARD_SIZE - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\b|%d\n", BOARD_SIZE - i);
    }
    printf("  %s  a b c d e f g h\n", HLINE);
    printf("  %s  %s(W)\n", HLINE, player1);
}