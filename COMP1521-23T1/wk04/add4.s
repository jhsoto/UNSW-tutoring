# Sum 4 numbers using functions

################################################################################
# .TEXT <main>
.text
main:
	# Args:     void
	#
	# Returns:  void
	#
	# Frame:    [$ra]
	# Uses:     [$a0, $a1, $a2, $a3, $v0]
	# Clobbers: [$a0, $a1, $a2, $a3, $v0]
	#
	# Locals:
	#
	# Structure:
	#   main
	#   -> [prologue]
	#       -> body
	#   -> [epilogue]
main__prologue:
	begin
	push	$ra		# Need to push $ra because we call another function

main__body:
	li	$a0, 5		# Setup arguments
	li	$a1, 7
	li	$a2, 10
	li	$a3, 23
	jal	add4		# Call add4(5, 7, 10, 23)

	move	$a0, $v0	# Return value in $v0
	li	$v0, 1		# printf("%d", result);
	syscall

	li	$a0, '\n'	# printf("\n");
	li	$v0, 11
	syscall

main__epilogue:
	pop	$ra
	end
	jr	$ra

#######################a#########################################################
# .TEXT <add4>
.text
add4:
	# Args:
	#	- $a0: int a
	#	- $a1: int b
	#	- $a2: int c
	#	- $a3: int d
	#
	# Returns:
	#	- $v0: int
	#
	# Frame:    [$ra, $s0, $s1, $s2]
	# Uses:     [$a0, $a1, $v0, $s0, $s1, $s2]
	# Clobbers: [$a0, $a1, $v0]
	#
	# Locals:
	#	- $s0: Save 'c' ($a2)
	#	- $s1: Save 'd' ($a3)
	#	- $s2: int res1
	#
	# Structure:
	#   add4
	#   -> [prologue]
	#       -> body
	#   -> [epilogue]

add4__prologue:
	begin
	push	$ra		# Need to push $ra because we call another function
	push	$s0		# Need to push all $s registers we use
	push	$s1
	push	$s2

	move	$s0, $a2
	move	$s1, $a3
add4__body:
	jal	add2		# 'a' and 'b' are already in $a0 and $a1
				# so we can just call add2 straight away
	
	move	$s2, $v0	# Save res1 in $s2
				# add2 could clobber the result if we store it in anything but an $s register

	move	$a0, $s0	# Move 'c' into $a0 from $s0 where we saved it earlier
	move	$a1, $s1	# Move 'd' into $a1
	jal	add2		# add2(c, d)

	move	$a0, $s2	# Move res1 into $a0 from $s2 where we saved it earlier
	move	$a1, $v0	# res2 was just returned so it is still in $v0
	jal	add2		# add2(res1, res2)
				# The final result is in $v0 already so we don't need to move it to return it
	
add4__epilogue:
	pop	$s2
	pop	$s1
	pop	$s0
	pop	$ra
	end
	jr	$ra

################################################################################
# .TEXT <add2>
.text
add2:
	# Args:
	#	- $a0: int x
	#	- $a1: int y
	#
	# Returns:
	#	- $v0: int
	#
	# Frame:    []
	# Uses:     [$v0, $t0]
	# Clobbers: [$v0, $t0]
	#
	# Locals:
	#	- $t0: x + y
	#
	# Structure:
	#   add2
	#   -> [prologue]
	#       -> body
	#   -> [epilogue]
add2__prologue:
	begin
	
add2__body:
	add	$t0, $a0, $a1

add2__epilogue:
	end
	move	$v0, $t0
	jr	$ra