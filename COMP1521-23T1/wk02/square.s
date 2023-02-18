# Prints the square of a number

main:
	# Locals:
	# 	- $t0: int x
	#	- $t1: int y

	# TODO - Translate this program to MIPS:
	# printf("Enter a number: ");
	# scanf("%d", &x);
	#
	# y = x * x;
	#
	# printf("%d\n", y);

	jr	$ra		# return


	.data
prompt_str:
	.asciiz "Enter a number: "