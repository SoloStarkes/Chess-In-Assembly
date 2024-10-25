# Chess in Assembly
.data 
# Starting messages:
starting_message_white: .asciiz "\nWelcome to chess! Please input the name for the white player (MAX 100 characters):  "
starting_message_black: .asciiz "\nPlease input the name for the black player (MAX 100 characters):  "
confirmation_white: .asciiz "\nWhite's name is: "
confirmation_black: .asciiz "\nBlack's name is: "

# reserve space for names 
white_name: .space 100 
black_name: .space 100

# "Clearing" screen 
clear: .asciiz "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

# Needed phrases 
invalid_move: .asciiz "\nInvalid move, try again\n"
valid_move: .asciiz "\nValid move\n"
takes_white: .asciiz "\nTakes white piece\n"
takes_black: .asciiz "\nTakes black piece\n"
white_move: .asciiz "\nWhite's move\n"
black_move: .asciiz "\nBlack's move\n"
game_over_text: .asciiz "\n Wins!\n"

# Define the board (8x8 grid)
board: .word  7, 8, 9, 10, 11, 12, 9, 8    # Row 1: Black major pieces
        .word 7, 7, 7, 7, 7, 7, 7, 7       # Row 2: Black pawns
        .word 0, 0, 0, 0, 0, 0, 0, 0       # Row 3: Empty
        .word 0, 0, 0, 0, 0, 0, 0, 0       # Row 4: Empty
        .word 0, 0, 0, 0, 0, 0, 0, 0       # Row 5: Empty
        .word 0, 0, 0, 0, 0, 0, 0, 0       # Row 6: Empty
        .word 1, 1, 1, 1, 1, 1, 1, 1       # Row 7: White pawns
        .word 2, 3, 4, 5, 6, 4, 3, 2       # Row 8: White major pieces
        
        
.text 
.globl main 


# main start to program 
# shouldn't need much else
main: 
# jump to player names 
jal player_names

#jump to main game loop
jal main_game_loop






# Gather player names
player_names: 
li $v0, 4 # system call code for printing string = 4
la $a0, starting_message_white 
syscall 

# Load user input for white name 
li $v0, 8 # sys call for reading and gathering input = 8
la $a0, white_name
li $a1, 100
syscall 

#Display that it was loaded correctly 

li $v0, 4 
la $a0, confirmation_white
syscall 

li $v0, 4
la $a0, white_name
syscall

# Starting message for black and input
li $v0, 4 
la $a0, starting_message_black
syscall 

# Load user input for black name 
li $v0, 8 
la $a0, black_name
li $a1, 100
syscall 

#Display that it was loaded correctly 
li $v0, 4 
la $a0, confirmation_black
syscall 

li $v0, 4
la $a0, black_name
syscall

jr $ra






# Main game loop
main_game_loop:

#1st get move from player
jal fetch_move


#2nd validate that move
jal validate_move

#If move is invalid, go back to start of loop
beq $v0, 0, main_game_loop 
 
# Update the board with the valid move   
jal update_board 
 
# Check if the game is over (checkmate/stalemate)   
jal check_game_over 

# If game over, break the loop
beq $v0, 1, game_over  

j main_game_loop  # Repeat the loop




game_over:
# Used to implement the end of the game infomration and terminate program 
li $v0, 10  
syscall



fetch_move: 
# TODO Need to implement a way to gather user input
# Shown below is an example of what a move may look like, but we need to get user input 
# It also souldn't be in the temporary registers for a procedure
  
    li $t0, 6  # From row
    li $t1, 4  # From column
    li $t2, 4  # To row
    li $t3, 4  # To column
    jr $ra     # Return to the caller



validate_move: 
# TODO Implement a system to determine a valid move 
# rest of code is a gpt example, but not final code, arguments still need to be determined to be put into the
# temporary registers. Do not go solely off the gpt code, it works kinda but not well
 # Ensure the move is within board boundaries (rows and columns between 0 and 7)





# Code to implement if an invalid move is proposed
# No TODO needed
invalid:
li $v0, 4 
la $a0, invalid_move
syscall 
li  $v0, 0         
jr  $ra                





update_board: 
# TODO Update the chess board for the next cycle, shown is an example hard code
la $t0, board # load enitre 2d array into t0

# Access needed piece 
li $t1, 3 # adjust value accordingly for the row
li $t2, 2 # adjust value accordingly for the column
li $t3, 8 # needed for the number of columns

# Calculate the offset in memory to locate row and column location
mul $t4, $t1, $t3 # t4 = row * cnumber of cols
add $t4, $t4, $t2 # t4 = row * cols + colunn 
sll $t4, $t4, 2 # muktiply by word
add $t5, $t0, $t4 # t5 = base + offset (address of chessboard[0][0])
lw $t6, 0($t5) # Load value from chessboard[0][0] into $t6 (should load the value 2 for the white rook)

li $v0, 1
move $a0, $t6
syscall



jr  $ra





check_game_over: 
# TODO Implement checking for end of game 
li $v0, 1
jr $ra
