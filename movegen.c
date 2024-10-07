#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "movegen.h"
#include "board.h"

bool is_valid_chess_coordinate(const char* coord) {
    // Check if the string is exactly 2 characters long
    if (strlen(coord) != 2) {
        return false;
    }

    // Check if the first character is between 'a' and 'h'
    if (coord[0] < 'a' || coord[0] > 'h') {
        return false;
    }

    // Check if the second character is between '1' and '8'
    if (coord[1] < '1' || coord[1] > '8') {
        return false;
    }

    // If both checks passed, it's a valid coordinate
    return true;
}

// Convert a chess coordinate to row and column indices
bool get_board_indices(const char* coord, int* row, int* col) {
    if (coord[0] >= 'a' && coord[0] <= 'h' && coord[1] >= '1' && coord[1] <= '8') {
        // Convert file (a-h) to column (0-7)
        *col = coord[0] - 'a';
        
        // Convert rank (1-8) to row (0-7)
        *row = BOARD_SIZE - (coord[1] - '0');  // Subtract '0' to convert char to int

        return true;
    }
    return false;
}

int validate_move(char board[BOARD_SIZE][BOARD_SIZE], int src_row, int src_col, int dest_row, int dest_col, int turn) {
    char piece = board[src_row][src_col];

    // Check if there is a piece at the source position
    if (piece == EMPTY) {
        return 0;
    }

    // Check if the piece belongs to the current player
    if ((turn == 1 && piece >= 'a' && piece <= 'z') || (turn == -1 && piece >= 'A' && piece <= 'Z')) {
        return 0;
    }

    // Implement movement rules for each piece type
    // Pawn movement
    if (piece == W_PAWN || piece == B_PAWN) {
        // Determine direction of movement based on the player
        int direction = (piece == W_PAWN) ? -1 : 1;  // White pawns move up (-1), black pawns move down (+1)

        // Forward movement (1 or 2 squares)
        if (src_col == dest_col) {
            // One square forward
            if (dest_row == src_row + direction && board[dest_row][dest_col] == EMPTY) {
                return 1;  // Valid move
            }
            // Two squares forward (only if it's the pawn's first move)
            if ((src_row == 6 && piece == W_PAWN) || (src_row == 1 && piece == B_PAWN)) {
                if (dest_row == src_row + 2 * direction && board[src_row + direction][src_col] == EMPTY && board[dest_row][dest_col] == EMPTY) {
                    return 1;  // Valid move
                }
            }
        }
        
        // Capture move (diagonally)
        if ((dest_col == src_col + 1 || dest_col == src_col - 1) && dest_row == src_row + direction) {
            if (board[dest_row][dest_col] != EMPTY && 
                ((piece == W_PAWN && board[dest_row][dest_col] >= 'a' && board[dest_row][dest_col] <= 'z') ||
                (piece == B_PAWN && board[dest_row][dest_col] >= 'A' && board[dest_row][dest_col] <= 'Z'))) {
                return 1;  // Valid capture
            }
        }

        return 0;  // Invalid pawn move
    }

    // Knight movement
    else if (piece == W_KNIGHT || piece == B_KNIGHT) {
        int row_diff = abs(dest_row - src_row);
        int col_diff = abs(dest_col - src_col);

        // Check for "L" shape movement: (2,1) or (1,2)
        if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)) {
            // Check if the destination is either empty or occupied by an opponent's piece
            char dest_piece = board[dest_row][dest_col];
            if (dest_piece == EMPTY || 
                (turn == 1 && dest_piece >= 'a' && dest_piece <= 'z') || 
                (turn == -1 && dest_piece >= 'A' && dest_piece <= 'Z')) {
                return 1;  // Valid knight move
            }
        }
        return 0;  // Invalid knight move
    }
    
    // Bishop movement
    else if (piece == W_BISHOP || piece == B_BISHOP) {
        // Check if the move is diagonal
        int row_diff = abs(dest_row - src_row);
        int col_diff = abs(dest_col - src_col);
        if (row_diff == col_diff) {
            // Check that the path is clear
            int row_direction = (dest_row > src_row) ? 1 : -1;  // Determine if moving up or down
            int col_direction = (dest_col > src_col) ? 1 : -1;  // Determine if moving right or left

            int current_row = src_row + row_direction;
            int current_col = src_col + col_direction;

            // Check each square along the diagonal path
            while (current_row != dest_row && current_col != dest_col) {
                if (board[current_row][current_col] != EMPTY) {
                    return 0;  // Path is blocked
                }
                current_row += row_direction;
                current_col += col_direction;
            }

            // Check if destination square is empty or occupied by an opponent's piece
            char dest_piece = board[dest_row][dest_col];
            if (dest_piece == EMPTY || 
                (turn == 1 && dest_piece >= 'a' && dest_piece <= 'z') || 
                (turn == -1 && dest_piece >= 'A' && dest_piece <= 'Z')) {
                return 1;  // Valid move
            }
        }
        return 0;  // Invalid bishop move (not diagonal or path blocked)
    }
    
    // Rook movement
    else if (piece == W_ROOK || piece == B_ROOK) {
        // Check if the move is in the same row or the same column
        if (src_row == dest_row || src_col == dest_col) {
            // Check that the path is clear
            if (src_row == dest_row) {  // Horizontal movement
                int col_direction = (dest_col > src_col) ? 1 : -1;  // Determine if moving right or left
                for (int col = src_col + col_direction; col != dest_col; col += col_direction) {
                    if (board[src_row][col] != EMPTY) {
                        return 0;  // Path is blocked
                    }
                }
            } else if (src_col == dest_col) {  // Vertical movement
                int row_direction = (dest_row > src_row) ? 1 : -1;  // Determine if moving up or down
                for (int row = src_row + row_direction; row != dest_row; row += row_direction) {
                    if (board[row][src_col] != EMPTY) {
                        return 0;  // Path is blocked
                    }
                }
            }

            // Check if the destination square is either empty or occupied by an opponent's piece
            char dest_piece = board[dest_row][dest_col];
            if (dest_piece == EMPTY || 
                (turn == 1 && dest_piece >= 'a' && dest_piece <= 'z') || 
                (turn == -1 && dest_piece >= 'A' && dest_piece <= 'Z')) {
                return 1;  // Valid rook move
            }
        }
        return 0;  // Invalid rook move (not horizontal or vertical, or path blocked)
    }
    
    // Queen movement
    else if (piece == W_QUEEN || piece == B_QUEEN) {
        int row_diff = abs(dest_row - src_row);
        int col_diff = abs(dest_col - src_col);

        // Check if the move is horizontal, vertical, or diagonal
        if (src_row == dest_row || src_col == dest_col || row_diff == col_diff) {
            // Handle horizontal or vertical movement (like a rook)
            if (src_row == dest_row) {  // Horizontal movement
                int col_direction = (dest_col > src_col) ? 1 : -1;  // Moving right or left
                for (int col = src_col + col_direction; col != dest_col; col += col_direction) {
                    if (board[src_row][col] != EMPTY) {
                        return 0;  // Path is blocked
                    }
                }
            } else if (src_col == dest_col) {  // Vertical movement
                int row_direction = (dest_row > src_row) ? 1 : -1;  // Moving up or down
                for (int row = src_row + row_direction; row != dest_row; row += row_direction) {
                    if (board[row][src_col] != EMPTY) {
                        return 0;  // Path is blocked
                    }
                }
            }
            // Handle diagonal movement (like a bishop)
            else if (row_diff == col_diff) {  // Diagonal movement
                int row_direction = (dest_row > src_row) ? 1 : -1;  // Moving up or down
                int col_direction = (dest_col > src_col) ? 1 : -1;  // Moving right or left

                int current_row = src_row + row_direction;
                int current_col = src_col + col_direction;
                while (current_row != dest_row && current_col != dest_col) {
                    if (board[current_row][current_col] != EMPTY) {
                        return 0;  // Path is blocked
                    }
                    current_row += row_direction;
                    current_col += col_direction;
                }
            }

            // Check if the destination square is either empty or occupied by an opponent's piece
            char dest_piece = board[dest_row][dest_col];
            if (dest_piece == EMPTY || 
                (turn == 1 && dest_piece >= 'a' && dest_piece <= 'z') || 
                (turn == -1 && dest_piece >= 'A' && dest_piece <= 'Z')) {
                return 1;  // Valid queen move
            }
        }
        return 0;  // Invalid queen move (not horizontal, vertical, or diagonal, or path blocked)
    }

    // King movement
    else if (piece == W_KING || piece == B_KING) {
        int row_diff = abs(dest_row - src_row);
        int col_diff = abs(dest_col - src_col);

        // Check if the move is one square in any direction
        if (row_diff <= 1 && col_diff <= 1) {
            // Check if the destination square is either empty or occupied by an opponent's piece
            char dest_piece = board[dest_row][dest_col];
            if (dest_piece == EMPTY || 
                (turn == 1 && dest_piece >= 'a' && dest_piece <= 'z') || 
                (turn == -1 && dest_piece >= 'A' && dest_piece <= 'Z')) {
                return 1;  // Valid king move
            }
        }
        return 0;  // Invalid king move
    }
    // If all checks pass
    return 1;
}
