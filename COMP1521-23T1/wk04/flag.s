# This program prints out a danish flag, by
# looping through the rows and columns of the flag.
# Each element inside the flag is a single character.
# (i.e., 1 byte).
# 
# (Dette program udskriver et dansk flag, ved at
# sløjfe gennem rækker og kolonner i flaget.)
# 

main:
	# Locals:
	#	- $t0: row
	#	- $t1: col
	# 	- $t2: &flag[i][j]
	#	- $t3: temp calculations

row_loop_init:
	li	$t0, 0				# int row = 0;
row_loop_cond:
	bge	$t0, FLAG_ROWS, row_loop_end	# while (row < FLAG_ROWS)

col_loop_init:
	li	$t1, 0				# int col = 0;
col_loop_cond:
	bge	$t1, FLAG_COLS, col_loop_end	# while (col < FLAG_COLS)

	# &flag[row][col] = &flag + 1 * ((row * FLAG_COLS) + col)
	#        base address ^     ^          ^              ^
	#     each item is one byte ^          ^              ^
	# each row we skip has FLAG_COLS items ^              ^
	#                go past col items in the desired row ^

	la	$t2, flag			# &flag
	mul	$t3, $t0, FLAG_COLS		# row * FLAG_COLS 	- items to skip to get to correct row
	add	$t3, $t3, $t1			# row * FLAG_COLS + col - total items to skip past
	add	$t2, $t2, $t3			# &flag[row][col] = &flag + 1 * ((row * FLAG_COLS) + col)

	lb	$a0, ($t2)			# printf("%c", flag[row][col]);
						# NOTE: we use 'lb' since we have an array of characters (bytes)
	li	$v0, 11
	syscall

	addi	$t1, $t1, 1			# col++;
	b	col_loop_cond
col_loop_end:

	li	$a0, '\n'			# printf("\n");
	li	$v0, 11
	syscall

	addi	$t0, $t0, 1			# row++;
	b	row_loop_cond

row_loop_end:

	jr	$ra

	.data
FLAG_ROWS = 6
FLAG_COLS = 12

# char flag[FLAG_ROWS][FLAG_COLS] =
flag:
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'
	.byte '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#'