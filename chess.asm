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
game_over_text: .asciiz "\n GAME OVER\n"
piece_row_integer: .asciiz "\nPlease enter the row integer for the piece you want to select:  "
piece_col_integer: .asciiz "\nPlease enter the column integer for the piece you want to select:  "
move_row_integer: .asciiz "\nPlease enter the row integer for the piece you want to move:  "
move_col_integer: .asciiz "\nPlease enter the column integer for the piece you want to move:  "

#Values needed for printing 
rows:   .word 8        # Number of rows
cols:   .word 8         # Number of columns
newline: .asciiz "\n"
space:   .asciiz " "

# Define the board (8x8 grid)
board:  .word  7, 8, 9, 10, 11, 9, 8, 
	7, 7, 7, 7, 7, 7, 7, 7, 7,
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	2, 3, 4, 5, 11, 4, 3, 2      
        
        
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
li $v0, 4           
la $a0, newline     
syscall
jal print_board 
#1st get move from player
jal fetch_move
 
# Update the board with the valid move, will directly change the value in the 2d array  
jal update_board 

j main_game_loop  # Repeat the loop




game_over:
# Used to implement the end of the game infomration and terminate program 
# Load user input for black name 
jal print_board
li $v0, 4
la $a0, game_over_text
li $a1, 100
syscall 
li $v0, 10  
syscall



fetch_move: 
# TODO Need to implement a way to gather user input
# Shown below is an example of what a move may look like, but we need to get user input 
# It also souldn't be in the temporary registers for a procedure
# Prompt the user
    li $v0, 4           # Syscall code for printing a string
    la $a0, piece_row_integer      # Load address of prompt string
    syscall

    # Read integer from user
    li $v0, 5           # Syscall code for reading an integer
    syscall
    move $t0, $v0       # Store the input integer in $t0

    # Prompt the user
    li $v0, 4           # Syscall code for printing a string
    la $a0, piece_col_integer      # Load address of prompt string
    syscall

    # Read integer from user
    li $v0, 5           # Syscall code for reading an integer
    syscall
    move $t1, $v0       # Store the input integer in $t1

# Prompt the user
    li $v0, 4           # Syscall code for printing a string
    la $a0, move_row_integer      # Load address of move_row_integer
    syscall

    # Read integer from user
    li $v0, 5           # Syscall code for reading an integer
    syscall
    move $t2, $v0       # Store the input integer in $t2

# Prompt the user
    li $v0, 4           # Syscall code for printing a string
    la $a0, move_col_integer      # Load address of move_col_integer
    syscall

    # Read integer from user
    li $v0, 5           # Syscall code for reading an integer
    syscall
    move $t3, $v0       # Store the input integer in $t3

# Store the values from $t0, $t1, $t2, $t3 to $a0, $a1, $a2, $a3
    move $a0, $t0
    move $a1, $t1
    move $a2, $t2
    move $a3, $t3



# Code to implement if an invalid move is proposed
# No TODO needed
invalid:
li  $v0, 1        
jr  $ra  

update_board: 
# TODO Update the chess board for the next cycle, shown is an example hard code
la $t0, board # load enitre 2d array into t0

# Access needed piece 
move $t1, $a0 # adjust value accordingly for the row 3
move $t2, $a1 # adjust value accordingly for the column 2
li $t3, 8 # needed for the number of columns


# Calculate the offset in memory to locate row and column location
mul $t4, $t1, $t3 # t4 = row * cnumber of cols
add $t4, $t4, $t2 # t4 = row * cols + colunn 
sll $t4, $t4, 2 # muktiply by word
add $t5, $t0, $t4 # t5 = base + offset (address of chessboard[0][0])
lw $t6, 0($t5) # Load value from chessboard[0][0] into $t6 (should load the value 2 for the white rook)
li $t7, 0
add $t7, $t7, $t6


# override previous location value
li $t1, 0  
sw $t1, 0($t5) 
lw $t6, 0($t5)

# Access needed piece 
move $t1, $a2 # adjust value accordingly for the row 5
move $t2, $a3 # adjust value accordingly for the column 2
li $t3, 8 # needed for the number of columns


# Calculate the offset in memory to locate row and column location
mul $t4, $t1, $t3 # t4 = row * cnumber of cols
add $t4, $t4, $t2 # t4 = row * cols + colunn 
sll $t4, $t4, 2 # muktiply by word
add $t5, $t0, $t4 # t5 = base + offset (address of chessboard[0][0])
lw $t6, 0($t5)


beq $t6, 11, game_over


sw $t7, 0($t5)
lw $t6, 0($t5)

jr  $ra


print_board:
    # Load number of rows and columns
    lw $t0, rows        # $t0 = number of rows
    lw $t1, cols        # $t1 = number of columns
    la $t2, board       # $t2 = base address of array

    li $s0, 0           # $s0 = row index (i = 0)
    j outer_loop

outer_loop:
    beq $s0, $t0, exit  # if i ==number of rows, exit outer loop

    li $s1, 0           # $s1 = column index (j = 0)

inner_loop:
    bge $s1, $t1, end_inner_loop  # if j >= number of columns, exit inner loop

    # Calculate the index: index = i * num_columns + j
    mul $t3, $s0, $t1   # $t3 = i * num_columns
    add $t3, $t3, $s1   # $t3 = $t3 + j

    # Calculate the address of the element: address = base_address + index * 4
    sll $t4, $t3, 2     # $t4 = index * 4 (element size is 4 bytes)
    add $t5, $t2, $t4   # $t5 = base_address + offset

    # Load the element
    lw $a0, 0($t5)      # $a0 = array[i][j]

    # Print the integer
    li $v0, 1           # Syscall code for print integer
    syscall

    # Print a space after each element
    li $v0, 4           # Syscall code for print string
    la $a0, space
    syscall

    # Increment column index j
    addi $s1, $s1, 1
    j inner_loop

end_inner_loop:
    # Print a newline after each row
    li $v0, 4           # Syscall code for print string
    la $a0, newline
    syscall

    # Increment row index i
    addi $s0, $s0, 1
    j outer_loop
exit: 
jr $ra
