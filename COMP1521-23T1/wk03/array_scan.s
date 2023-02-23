# Stores 10 numbers scanned from input into an array

main:
	# Locals:
	#	- $t0: int i
	### TODO: expand for address calculations...

	li	$t0, 0				# int i = 0;
for_cond:
	bge	$t0, ARRAY_SIZE, for_exit	# while(i < ARRAY_SIZE)
for_body:
	### TODO: Convert this C code to MIPS
	# scanf("%d", &array[i]);
	
	addi	$t0, $t0, 1			# i++;
	b	for_cond

for_exit:
	jr	$ra				# return 0;
	

	.data
# define ARRAY_SIZE = 10
ARRAY_SIZE = 10

# int array[ARRAY_SIZE];
array:
	.space ARRAY_SIZE * 4