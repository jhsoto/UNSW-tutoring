# Prints the square of a number

main:
	# Locals:
	# 	- $t0: int x
	#	- $t1: int y

	la	$a0, prompt_str	# printf("Enter a number: ")
	li	$v0, 4		# Syscall 4 - print string
	syscall

	li	$v0, 5		# scanf("%d", &x);
	syscall			# Syscall 5 - read int
	move	$t0, $v0	# Result of read stored in $v0

	mul	$t1, $t0, $t0	# y = x * x;

	move	$a0, $t1	# printf("%d", y);
	li	$v0, 1		# Sycall 1 - print int
	syscall

	li	$a0, '\n'	# printf("\n");
	li	$v0, 11		# Syscall 11 - print character
	syscall

	li	$v0, 0		# return 0
	jr	$ra


	.data
prompt_str:
	.asciiz "Enter a number: "