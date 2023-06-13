# Create and print a struct of favourite things

main:
	la	$t0, faves

	li	$t1, 7			# faves.number = 7;
	sw	$t1, ($t0)		# faves.number is the first field, 
					# so it is stored immediately after the label.

	li	$t1, 'Q'		# faves.letter = 'Q';
	sw	$t1, 4($t0)		# faves.letter is the second field,
					# so it is stored AFTER the first field.
					# In this case, 4 bytes (an integer) after.

	la	$a0, fave_number_str	# printf("My favourite number is: ");
	li	$v0, 4
	syscall

	lw	$a0, ($t0)		# printf("%d", faves.number);
	li	$v0, 1
	syscall

	li	$a0, '\n'		# printf("\n");
	li	$v0, 11
	syscall
	
	la	$a0, fave_letter_str	# printf("My favourite letter is: ");
	li	$v0, 4
	syscall
	
	lw	$a0, 4($t0)		# printf("%c", faves.letter);
	li	$v0, 11
	syscall

	li	$a0, '\n'		# printf("\n");
	li	$v0, 11
	syscall

	li	$v0, 0			# return 0
	jr	$ra

	.data
fave_number_str:
	.asciiz "My favourite number is: "
fave_letter_str:
	.asciiz "My favourite letter is: "

	.align 2		# We need this align so that our struct starts on a 4 byte boundary.
				# Unaligned accesses result in errors!
				# .align N - aligns to nearest 2^N boundary
				# e.g.
				# | 1 | _ | _ | _ | _ |  (each |_| is a byte, starting on a multiple of 4)
				# .align 1 fills in the following with padding:
				# | 1 | 0 | _ | _ | _ |
				# .align 2 fills in the following with padding:
				# | 1 | 0 | 0 | 0 | _ |
	
	# Here is our struct definition:
	# struct favourite {
	#     int number;
	#     char letter;
	# };
faves:
	.space 5		# We reserve 5 bytes: 4 for the number and 1 for the letter (in that order).
				# The number and letter are stored sequentially, just like an array but with different types.