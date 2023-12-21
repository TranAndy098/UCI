#                                           ICS 51, Lab #2
# 
#                                          IMPORTANT NOTES:
# 
#                       Write your assembly code only in the marked blocks.
# 
#                       DO NOT change anything outside the marked blocks.
#
#

###############################################################
#                           Text Section
.text

###############################################################
###############################################################
###############################################################
#                            PART 1 (Fibonacci)
#
# 	The Fibonacci Sequence is the series of integer numbers:
#
#		0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

#	The next number is found by adding up the two numbers before it.
	
#	The `2` is found by adding the two numbers before it (1+1)
#	The `3` is found by adding the two numbers before it (1+2),
#	And the `5` is (2+3),
#	and so on!
#
# You should compute N ($a0) number of elements of fibonacci and put
# in array, named fib_array.
# 
fibonacci:
# $a0: Number of elements. 
# fib_array: The destination array.
################## Part 1: your code begins here ###############

la $t7, fib_array # get address of fib_array

addi $s7, $zero, 0 # start with 0 
sw $s7, ($t7) # store 0

addi $t7, $t7, 4 # get to next address
addi $s6, $zero, 1 # start with 1
sw $s6, ($t7) # store 2

addi $t6, $zero, 2 # intialize count to 2 for 0 and 1
# s7 will be the 2 previous number
# s6 will be the 1 previous number

while_fibonacci:

beq $t6, $a0, end_fibonacci # check if the count is equal to N, if so end
addi $t7, $t7, 4 # get to next address
add $s5, $s7, $s6 # s5 is sum of two previous numbers, s7 and s6
sw $s5, ($t7) # store s5
addi $s7, $s6, 0 # make the 2 previous number, the 1 previous number
addi $s6, $s5, 0 # make the 1 previous number, the number we just got
addi $t6, $t6, 1 # increment the count
j while_fibonacci

end_fibonacci:

############################## Part 1: your code ends here   ###
jr $ra

###############################################################
###############################################################
###############################################################
#                  PART 2 (local maximum points)
# Write a function in MIPS assembly that takes an array of 
# integers and finds local maximum points. i.e., points that if 
# the input entry is larger than both adjacent entries. The 
# output is an array of the same size of the input array. The 
# output point is 1 if the corresponding input entry is a 
# relative maximum, otherwise 0. (You should ignore the output
# array's boundary items, set to 0.) 
# 
# For example,
# 
# the input array of integers is {1, 3, 2, 4, 6, 5, 7, 8}. Then,
# the output array of integers should be {0, 1, 0, 0, 1, 0, 0, 0}
# 
# (Note: The first/last entry of the output array is always 0
#  since it's ignored, never be a local maximum.)
# $a0: The base address of the input array
# $a1: The base address of the output array with local maximum points
# $a2: Size of array
find_local_maxima:
############################ Part 2: your code begins here ###
# idea: store 0 and while loop go to one less than size then add 0 to output array

addi $t7, $zero, 0
sw $t7, ($a1) # store 0 for the first index

addi $t7, $t7, 2 # starts at count at 2 becasue first and last will exist outside of loop

while_local_maxima:
beq $t7, $a2, end_local_maxima # exit when the inner size (N - 2) loops through
addi $a0, $a0, 4 # moves input address to the next
addi $a1, $a1, 4 # moves output address to the next
lw $t4, -4($a0) # previous
lw $t5, ($a0) # current
lw $t6, 4($a0) # next 

addi $s7, $zero, 0 # start number at 0 

blt $t5, $t4, if_end_local_maxima # if current is less than preiovus, cannot be local maxima, so branch to else
blt $t5, $t6, if_end_local_maxima # if current is less than next, cannot be local maxima, so branch to else
addi $s7, $s7, 1 # if previous < current > next, then local maxima, so incremnt number to 1

if_end_local_maxima:
sw $s7, ($a1) # store number either 0 or 1
addi $t7, $t7, 1 # incremnet counter
j while_local_maxima

end_local_maxima:
addi $a1, $a1, 4 # moves to last address
addi $t7, $zero, 0
sw $t7, ($a1) # store 0 for the last index

############################ Part 2: your code ends here ###
jr $ra

###############################################################
###############################################################
###############################################################
#                       PART 3 (Change Case)
# Complete the change_case function that takes a Null-terminated
# string and converts the lowercase characters (a-z) to 
# uppercase and convert the uppercase ones (A-Z) to lower case. 
# Your function should also ignore non-alphabetical characters. 
# For example, "L!A##b@@3" should be converted to "laB". 
# In null-terminated strings, end of the string is specified 
# by a special null character (i.e., value of 0).

#a0: The base address of the input array
#a1: The base address of the output array
###############################################################
change_case:
############################## Part 3: your code begins here ###
# if asscii in range of upper add 20 and vice versa

lb $t7, ($a0) # take the first byte


while_change_case:
beq $t7, 0, end_change_case

addi $s7, $zero, 0

blt $t7, 65, else_change_case # if it is not 65 or greater it cannot be a letter
bgt $t7, 122, else_change_case # if it is not 122 or less it cannot be a letter 

upper_test:
bgt $t7, 90, lower_test # if it is not 90 or less it cannot be an upper, but still test if lower
addi $s7, $t7, 32
j letter


lower_test:
blt $t7, 97, else_change_case # if it is not 97 or greater it cannot be a lower
addi $s7, $t7, -32


letter:
sb $s7, ($a1) # stores resulting byte
addi $a1, $a1, 1 # incremnet output address to next byte address, if stored

else_change_case:

addi $a0, $a0, 1 # increment input address to next byte address
lb $t7, ($a0) # take the next byte

j while_change_case


end_change_case:
addi $s7, $zero, 0
sb $s7, ($a1)

############################## Part 3: your code ends here ###
jr $ra
