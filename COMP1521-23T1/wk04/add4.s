# Sum 4 numbers using functions

################################################################################
# .TEXT <main>
.text
main:
	# Args:     void
	#
	# Returns:  void
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   main
	#   -> [prologue]
	#       -> body
	#   -> [epilogue]
main__prologue:
	begin

main__body:
	### TODO: Translate the following C code to MIPS
	# int result = add4(5, 7, 10, 23);


	li	$a0, 42		# printf("%d", result);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("\n");
	li	$v0, 11
	syscall

main__epilogue:
	end
	jr	$ra

################################################################################
# .TEXT <add4>
.text
add4:
	# Args:     void
	#
	# Returns:  void
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   add4
	#   -> [prologue]
	#       -> body
	#   -> [epilogue]

add4__prologue:
	begin
add4__body:
	### TODO: Translate the following C code to MIPS
	# int res1 = add2(a, b);
	# int res2 = add2(c, d);
	# return add2(res1, res2);
add4__epilogue:
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