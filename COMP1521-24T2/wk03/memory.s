# Explores some memory address arithmetic!

main:
	# Locals:
	#	- $t0: Address to read from

	### TODO: Change this and see what gets printed out!
	# Some example addresses:
	#   - first		-> 100
	#   - second		-> 41
	#   - first + 4 	-> 41
	#   - second + 8	-> 43
	#   - second + 2	-> unaligned address! (error)
	#   - third (lw)	-> 1214606444 (hex: 0x48656C6C, from the characters "Hell")
	#   - third (lb)        -> the character 'H' (decimal: 72, hex: 0x48)
	#   - third + 3 (lb)	-> the character 'l' (decimal: 108, hex: 0x6C)
	la	$t0, first

	lw	$a0, ($t0)		# print out the value read from memory as an integer
	li	$v0, 1
	syscall

	li	$v0, 0			# return 0;
	jr	$ra

	.data
first:
	.word 100
second:
	.word 41, 42, 43
third:
	.byte 'H', 'e', 'l', 'l', 'o', '!', '\0'
