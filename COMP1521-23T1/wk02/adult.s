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

	bge	$t0, 18, adult		# if (age >= 18) -> adult
	b	not_adult		# else -> not_adult
not_adult:
	la	$a0, not_adult_str	# printf("You are not an adult.\n");
	li	$v0, 4
	syscall

	b	epilogue		# Without this we would print adult_str too!

adult:
	la	$a0, adult_str		# printf("You are an adult!\n");
	li	$v0, 4
	syscall

epilogue:
	jr	$ra

	.data
prompt_str:
	.asciiz "Enter your age: "
adult_str:
	.asciiz "You are an adult!\n"
not_adult_str:
	.asciiz "You are not an adult.\n"