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

	# TODO - Translate this program to MIPS:
	# for (int i = 1; i <= n; i++) {
	#     fac *= i;
	# }

	la	$a0, result_str		# printf("n! = ");
	li	$v0, 4
	syscall
	
	move	$a0, $t1		# printf("%d", fac);
	li	$v0, 1
	syscall
	
	li	$a0, '\n'		# printf("\n");
	li	$v0, 11
	syscall

	jr	$ra			# return


	.data
prompt_str:
	.asciiz "n = "
result_str:
	.asciiz "n! = "