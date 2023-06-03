# Calculates the factorial of a number (NOT recursively)

main:
	# Locals:
	# 	- $t0: int n
	#	- $t1: int fac
	#	- $t2: int i

	la	$a0, prompt_str		# printf("n = ");
	li	$v0, 4
	syscall
	
	li	$v0, 5			# scanf("%d", &n);
	syscall
	move	$t0, $v0

	li	$t1, 1			# int fac = 1;

fac_loop_init:				# for (int i = 1; i <= n; i++) {
	li	$t2, 1			# int i = 1;

fac_loop_cond:
	bgt	$t2, $t0, fac_loop_end	# if (i > n) -> exit loop

fac_loop_body:
	mul	$t1, $t1, $t2		# fac *= i

fac_loop_inc:
	addi	$t2, $t2, 1		# i++;

	b	fac_loop_cond		# Go back to loop condition

fac_loop_end:
	la	$a0, result_str		# printf("n! = ");
	li	$v0, 4
	syscall
	
	move	$a0, $t1		# printf("%d", fac);
	li	$v0, 1
	syscall
	
	li	$a0, '\n'		# printf("\n");
	li	$v0, 11
	syscall

	li	$v0, 0			# return 0
	jr	$ra


	.data
prompt_str:
	.asciiz "n = "
result_str:
	.asciiz "n! = "