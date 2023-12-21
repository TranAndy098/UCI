.include "lab1.asm"

###############################################################
#                           Data Section
.data
# 

new_line: .asciiz "\n"
space: .asciiz " "
triple_range_lbl: .asciiz "\nTriple range (Decimal Values) \nExpected output:\n240000 0 -300\nObtained output:\n"
swap_bits_lbl: .asciiz "\nSwap bits (Hexadecimal Values)\nExpected output:\n55555555 FDEC7564 02138A9B\nObtained output:\n"
det_lbl: .asciiz "\nDeterminant \nExpected output:\n-2 2 -2\nObtained output:\n"

swap_bits_test_data:  .word 0xAAAAAAAA, 0xFEDCBA98, 0x01234567
swap_bits_expected_data:  .word 0x55555555, 0xFDEC7564, 0x02138A9B

triple_range_test_data: .word 80000, 111, 0, -111, 11
triple_range_expected_data: .word 240000, 0, -300

det_test_data: .word 0x10002, 0x30004, 0xFFFFFFFE, 0x30004, 0xFFFF0002, 0x3FFFC
det_expected_data: .word -2, 2, -2


hex_digits: .byte '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'

###############################################################
#                           Text Section
.text
.globl main

# Utility function to print hexadecimal numbers
print_hex:
move $t0, $a0
li $t1, 8 # digits
lui $t2, 0xf000 # mask
mask_and_print:
# print last hex digit
and $t4, $t0, $t2 
srl $t4, $t4, 28
la    $t3, hex_digits  
add   $t3, $t3, $t4 
lb    $a0, 0($t3)            
li    $v0, 11                
syscall 
# shift 4 times
sll $t0, $t0, 4
addi $t1, $t1, -1
bgtz $t1, mask_and_print
exit:
jr $ra

###############################################################
###############################################################
###############################################################
#                          Main Function 
main:
################################
# Print part 1 information
li $v0, 4
la $a0, new_line
syscall
la $a0, swap_bits_lbl
syscall

# Testing part 1
li $s0, 3 # num of test cases
li $s1, 0
la $s2, swap_bits_test_data

test_p1:
add $s4, $s2, $s1
# Pass input parameter
lw $a0, 0($s4)
jal swap_bits

move $a0, $v0
jal print_hex
li $v0, 4
la $a0, space
syscall

addi $s1, $s1, 4
addi $s0, $s0, -1
bgtz $s0, test_p1

################################
# Print part 2 information

li $v0, 4
la $a0, new_line
syscall
la $a0, triple_range_lbl
syscall


# Testing part 2
li $s0, 3 # num of test cases
li $s1, 0
la $s2, triple_range_test_data

test_p2:
add $s4, $s2, $s1
# Pass input parameter
lw $a0, 0($s4)
lw $a1, 4($s4)
lw $a2, 8($s4)
jal triple_range

move $a0, $v0        # $integer to print
li $v0, 1
syscall

li $v0, 4
la $a0, space
syscall

addi $s1, $s1, 4
addi $s0, $s0, -1
bgtz $s0, test_p2

################################
# Print part3 information

li $v0, 4
la $a0, new_line
syscall
la $a0, det_lbl
syscall

# Testing part 3
li $s0, 3 # num of test cases
li $s1, 0
la $s2, det_test_data

test_p3:
add $s4, $s2, $s1
# Pass input parameter
lw $a0, 0($s4)
lw $a1, 4($s4)
jal determinant

move $a0, $v0        # $integer to print
li $v0, 1
syscall

li $v0, 4
la $a0, space
syscall

addi $s1, $s1, 8
addi $s0, $s0, -1
bgtz $s0, test_p3


_end:
# end program
li $v0, 10
syscall

