# Replace all negative numbers in an array with zero

main:
	# Locals:
	#	- $t0: int i
	### TODO: expand for address calculations...

	li	$t0, 0				# int i = 0;
for_cond:
	bge	$t0, ARRAY_SIZE, for_exit	# while(i < ARRAY_SIZE)
for_body:
	### TODO: Convert this C code to MIPS
	# if (numbers[i] < 0) {
        #     numbers[i] = 0;
        # }
	
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