# Sum 2 numbers using functions

main:
main__prologue:
	begin

main__body:
	### TODO: Translate the following C code to MIPS
	# int result = add2(5, 7);

	
	li	$a0, 42		# printf("%d", result);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("\n");
	li	$v0, 11
	syscall

main__epilogue:
	end
	jr	$ra


add2:
add2__prologue:
	begin
add2__body:
	### TODO: Translate the following C code to MIPS
	# return x + y;
add2__epilogue:
	end
	jr	$ra
