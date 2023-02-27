# Replace all negative numbers in an array with zero

main:
	# Locals:
	#	- $t0: int i
	#	- $t1: temporary calculations
	#	- $t2: numbers[i]

	li	$t0, 0				# int i = 0;
for_cond:
	bge	$t0, ARRAY_SIZE, for_exit	# while(i < ARRAY_SIZE)
for_body:
	mul	$t1, $t0, 4			# $t1 = 4 * i
	lw	$t2, numbers($t1)		# Load numbers[i] into $t2
						# The syntax there is a bit strange, but very compact
						# In general, x($y) in lw/sw uses the address ($y + x)
						# x is a constant offset, $y is some value in a register
						# Here, the address used is: $t1 + numbers = numbers + (4 * i) = numbers[i]
	
	bgez	$t2, not_negative		# if (numbers[i] >= 0) -> Don't change to zero

	sw	$0, numbers($t1)		# numbers[i] = 0;
						# $0 is a special register that ALWAYS has the number 0 in it

not_negative:
	
	addi	$t0, $t0, 1			# i++;
	b	for_cond

for_exit:
	jr	$ra				# return 0;
	

	.data
# define ARRAY_SIZE = 10
ARRAY_SIZE = 10

# int numbers[ARRAY_SIZE];
numbers:
	.word 1, -2, 3, 4, -5, 6, 7, -8, -9, 10