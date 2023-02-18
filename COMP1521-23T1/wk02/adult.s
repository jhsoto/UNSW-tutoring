# Determines if someone is an adult

main:
	# Locals:
	#	- $t0: int age

	la	$a0, prompt_str		# printf("Enter your age: ");
	li	$v0, 4
	syscall

	li	$v0, 5			# scanf("%d", &age);
	syscall
	move	$t0, $v0

	# TODO - Translate the rest of this program:
	# if (age >= 18) {
	#     printf("You are an adult!\n");
	# } else {
	#     printf("You are not an adult.\n");
	# }

epilogue:
	jr	$ra

	.data
prompt_str:
	.asciiz "Enter your age: "
adult_str:
	.asciiz "You are an adult!\n"
not_adult_str:
	.asciiz "You are not an adult.\n"