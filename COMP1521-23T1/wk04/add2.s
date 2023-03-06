# Sum 2 numbers using functions

main:
main__prologue:
	begin
	push	$ra		# We push $ra because jal will change $ra
				# We need to save this old $ra value so we can correctly exit main

main__body:
	li	$a0, 5		# First argument is 5
	li	$a1, 7		# Second argument is 7
	jal	add2		# Call add2(5, 7)

	# $ra changes to point here after the jal
	move	$a0, $v0	# Return value is in $v0
	li	$v0, 1		# printf("%d", result);
	syscall

	li	$a0, '\n'	# printf("\n");
	li	$v0, 11
	syscall

main__epilogue:
	pop	$ra		# We restore the old value of $ra so we return to the correct point
	end			# If we don't push/pop $ra, the next jump will send us back to right after the jal
	jr	$ra


add2:
# int add2(int x, int y)
#  ^         ^      ^
# $v0       $a0    $a1
add2__prologue:
	begin
add2__body:
	add	$v0, $a0, $a1	# Arguments are in $a0 and $a1
add2__epilogue:
	end
	jr	$ra
