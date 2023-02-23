# Multiply a global variable by 2

main:
	# Locals:
	#	- $t0: &my_number    (address of my_number)
	#	- $t1: my_number
	
	la	$a0, before_multiply	# printf("My number is: ");
	li	$v0, 4
	syscall

	### TODO: change this to print my_number instead of 42
	li	$a0, 42			# printf("%d", my_number);
	li	$v0, 1
	syscall

	li	$a0, '\n'		# printf("\n");
	li	$v0, 11
	syscall

	
	### TODO: Translate this C code to MIPS
	# my_number = my_number * 2;


	la	$a0, after_multiply	# printf("Now my number is: ");
	li	$v0, 4
	syscall

	### TODO: change this to print my_number instead of 42
	li	$a0, 42			# printf("%d", my_number);
	li	$v0, 1
	syscall

	li	$a0, '\n'		# printf("\n");
	li	$v0, 11
	syscall

	jr	$ra			# return 0;


	.data
# This is the global variable
my_number:
	.word 10

before_multiply:
	.asciiz "My number is: "
after_multiply:
	.asciiz "Now my number is: "