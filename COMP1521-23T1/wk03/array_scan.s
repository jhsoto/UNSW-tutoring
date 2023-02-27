# Stores 10 numbers scanned from input into an array

main:
	# Locals:
	#	- $t0: int i
	#	- $t1: temp location to store scan result
	#	- $t2: &array[i]
	#	- $t3: temporary results

	li	$t0, 0				# int i = 0;
for_cond:
	bge	$t0, ARRAY_SIZE, for_exit	# while(i < ARRAY_SIZE)
for_body:
	li	$v0, 5				# scanf("%d", &temp);
	syscall
	move	$t1, $v0			# Store scan temporarily in $t1 while we calculate array address...

						# Array starts at &array (0th element), so to reach the ith element, we skip past i elements.
						# Each element is an int, which is 4 bytes, so we skip (4 * i) bytes.
	la	$t2, array			# &array in $t2
	mul	$t3, $t0, 4			# 4 * i in $t3
	add	$t2, $t2, $t3			# &array[i] = &array + (4 * i)

	sw	$t1, ($t2)			# Store 4 bytes of $t1 (scan result) at the address stored in $t2 (&array[i])
						# &array[i] = temp
	
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