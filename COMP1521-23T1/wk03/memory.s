# Explores some memory address arithmetic!

main:
	# Locals:
	#	- $t0: Address to read from

	### TODO: Change this and see what gets printed out!
	la	$t0, first

	lw	$a0, ($t0)		# print out the value read from memory as an integer
	li	$v0, 1
	syscall

	jr	$ra

	.data
first:
	.word 100
second:
	.word 41, 42, 43
third:
	.byte 'H', 'e', 'l', 'l', 'o', '!', '\0'
