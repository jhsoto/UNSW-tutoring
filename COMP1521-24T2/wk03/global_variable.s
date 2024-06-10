# Multiply a global variable by 2

main:
	# Locals:
	#	- $t0: &my_number    (address of my_number)
	#	- $t1: my_number
	
	la	$a0, before_multiply	# printf("My number is: ");
	li	$v0, 4
	syscall

	la	$t0, my_number		# &my_number in $t0
	lw	$t1, ($t0)		# Load 4 bytes from the address in $t0 (&my_number), into $t1
					# At this point, $t1 = my_number
	
	move	$a0, $t1		# printf("%d", my_number);
	li	$v0, 1
	syscall

	li	$a0, '\n'		# printf("\n");
	li	$v0, 11
	syscall

	la	$t0, my_number		# &my_number in $t0
	lw	$t1, ($t0)		# Load 4 bytes from the address in $t0 (&my_number), into $t1
					# At this point, $t1 = my_number
	mul	$t1, $t1, 2		# $t1 = my_number * 2;
					# NOTE: $t1 has been changed, my_number (the global variable) has not!
	sw	$t1, my_number		# Store $t1 back into my_number
					# Technically, my_number here is a constant offset to the address 0x00, but this isn't too important :)

	la	$a0, after_multiply	# printf("Now my number is: ");
	li	$v0, 4
	syscall

	la	$t0, my_number		# &my_number in $t0
	lw	$t1, ($t0)		# Load 4 bytes from the address in $t0 (&my_number), into $t1
					# At this point, $t1 = my_number
	
	move	$a0, $t1		# printf("%d", my_number);
	li	$v0, 1
	syscall

	li	$a0, '\n'		# printf("\n");
	li	$v0, 11
	syscall

	li	$v0, 0			# return 0;
	jr	$ra


	.data
# This is the global variable
my_number:
	.word 10

before_multiply:
	.asciiz "My number is: "
after_multiply:
	.asciiz "Now my number is: "