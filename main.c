#include <stdio.h>
#include "board.h"
#include "movegen.h"

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    char move[3];
    char player1[16];
    char player2[16];
    int turn = WHITE;
    int game_over = 0;

    // Initialize and display the board
    printf("Welcome to the chess game! Enter the white user's name (max 12 characters): ");
    scanf("%15s", player1);
    printf("Enter the black user's name (max 12 characters): ");
    scanf("%15s", player2);
    initialize_board(board);
    display_board(board, player1, player2);

    // Gather user input for a move
    printf("Select your piece (a1 to h8): ");
    scanf("%2s", move); // This will capture a single character

    printf("You entered: %2s\n", move);

    return 0;
}