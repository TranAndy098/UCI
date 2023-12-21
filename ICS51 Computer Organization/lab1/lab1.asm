#                                           ICS 51, Lab #1
# 
#                                          IMPORTATNT NOTES:
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
#                            PART 1 (Swap Bits)
# 
# You are given an 32-bits integer stored in $a0. You need swap the bits
# at odd and even positions. i.e. b31 <-> b30, b29 <-> b28, ... , b1 <-> b0
# 
# Implementation details:
# The integer is stored in register $a0. You need to store the answer 
# into register $v0 in order to be returned by the function to the caller.
swap_bits:
############################## Part 1: your code begins here ###

andi $s6, $a0, 2863311530 #taking all the bits in odd places
srl $s6, $s6, 1 #shifting odd places to the right for even places

andi $s7, $a0, 1431655765 #taking all the bits in even places
sll $s7, $s7, 1 #shifting even places to the left for odd places

or $v0, $s6, $s7 #or the seperate odd and even places to combine into one 

############################## Part 1: your code ends here ###
jr $ra

###############################################################
###############################################################
###############################################################
#                           PART 2 (Triple Range)
# 
# You are given three integers. You need to find the smallest 
# one and the largest one and multiply their sum by three and return it.
# 
# Implementation details:
# The three integers are stored in registers $a0, $a1, and $a2. You 
# need to store the answer into register $v0 in order to be returned by 
# the function to the caller.
triple_range:
############################### Part 2: your code begins here ##
#if a < b
bgt $a0, $a1, a_g_b #if a > b then go to a_g_b, stay if a < b

#if a < b and b < c
bgt $a1, $a2, b_g_c #if b > c then go to b_g_c, stay if b < c
add $s7, $zero, $a2 #c is the greatest
add $s6, $zero, $a0 #a is the least
j after

#if a < b and b > c
b_g_c:

#if a < b and b > c and a < c
bgt $a0, $a2, a_g_c #if a > c then go to a_g_c, stay if a < c
add $s7, $zero, $a1 #b is the greatest
add $s6, $zero, $a0 #a is the least
j after

#if a < b and b > c and a > c
a_g_c:
add $s7, $zero, $a1 #b is the greatest
add $s6, $zero, $a2 #c is the least
j after


#if a > b
a_g_b:

#if a > b and b > c
bgt $a2, $a1, c_g_b
add $s7, $zero, $a0 #a is the greatest
add $s6, $zero, $a2 #c is the least
j after

#if a > b and b < c and a < c
c_g_b:
bgt $a0, $a2, a_g_c_g_b
add $s7, $zero, $a2 #c is the greatest
add $s6, $zero, $a1 #b is the least
j after

#if a > b and b < c and a > c
a_g_c_g_b:
add $s7, $zero, $a0 #a is the greatest
add $s6, $zero, $a1 #b is the least
j after

after: # once max and min have been found $s6 < $s7
add $s5, $s6, $s7
sll $s4, $s5, 1
add $v0, $s4, $s5

############################### Part 2: your code ends here  ##
jr $ra

###############################################################
###############################################################
###############################################################
#                            PART 3 (Determinant)
# 
# You are given a 2x2 matrix and each element is a 16-bit 
# signed integer. Calculate its determinant.
# 
# Implementation details:
# The four 16-bit integers are stored in registers $a0, $a1. 
# You need to store the answer into register $v0 in order to 
# be returned by the function to the caller.
determinant:
############################## Part 3: your code begins here ###
andi $s6, $a0, 0x0000FFFF #b

andi $s5, $s6, 0x00008000 # checking if 15th index is 1

bne $s5, 32768, b_is_good #checks if b needs to have 1's infront to keep sign 
ori $s6, $s6, 0xFFFF0000 #gives b 1's to keep sign

b_is_good:

andi $s7, $a0, 0xFFFF0000 
sra $s7, $s7, 16 #a



andi $t6, $a1, 0x0000FFFF #d

andi $s5, $t6, 0x00008000 # checking if 15th index is 1

bne $s5, 32768, d_is_good #checks if d needs to have 1's infront to keep sign 
ori $t6, $t6, 0xFFFF0000 #gives d 1's to keep sign

d_is_good:


andi $t7, $a1, 0xFFFF0000 
sra $t7, $t7, 16 #c


mult $s7, $t6 #a * d
mflo $s7



mult $s6, $t7 #b * c
mflo $s6

sub $v0, $s7, $s6

############################## Part 3: your code ends here ###
jr $ra

