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

	# TODO - Translate the rest of this program:
	# if (age >= 13 && age <= 19) {
	#     printf("You are a teenager!\n");
	# } else {
	#     printf("You are not a teenager.\n");
	# }

epilogue:
	jr	$ra

	.data
prompt_str:
	.asciiz "Enter your age: "
teenager_str:
	.asciiz "You are a teenager!\n"
not_teenager_str:
	.asciiz "You are not a teenager.\n"