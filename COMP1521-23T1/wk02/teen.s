# Determines if someone is a teenager

main:
	# Locals:
	#	- $t0: int age

	la	$a0, prompt_str		# printf("Enter your age: ");
	li	$v0, 4
	syscall

	li	$v0, 5			# scanf("%d", &age);
	syscall
	move	$t0, $v0

					# Here we flip the condition to be more like:
					# if (age < 13 || age > 19) -> not_teenager

	blt	$t0, 13, not_teenager	# if (age < 13) -> not_teenager
	bgt	$t0, 19, not_teenager	# if (age > 19) -> not_teenager
					# At this point, they have to be a teenager!
teenager:
	la	$a0, teenager_str	# printf("You are a teenager!\n");
	li	$v0, 4
	syscall

	b	epilogue

not_teenager:
	la	$a0, not_teenager_str	# printf("You are not a teenager.\n");
	li	$v0, 4
	syscall

epilogue:
	jr	$ra

	.data
prompt_str:
	.asciiz "Enter your age: "
teenager_str:
	.asciiz "You are a teenager!\n"
not_teenager_str:
	.asciiz "You are not a teenager.\n"