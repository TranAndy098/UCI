.include "lab2.asm"

###############################################################
#                           Data Section
.data

new_line: .asciiz "\n"
space: .asciiz " "
comma: .asciiz ", "

fibonacci_label: .asciiz "\nTesting Fibonacci: fib(5)\n"
fibonacci_lbl: 	.asciiz "Expected output:\n0, 1, 1, 2, 3\nObtained output:\n"

find_local_maxima_label: .asciiz "\nTesting local maximum points: 1, 3, 2, 4, 6, 5, 7, 8\n"
find_local_maxima_lbl: .asciiz "Expected output:\n0, 1, 0, 0, 1, 0, 0, 0\nObtained output:\n"

changecase_label: .asciiz "\nTesting Change Case: cA+SH$$$___rU*LE S^^eVE@RY~~th~ing_aRO=/[]UND_mE:|\n"
change_case_expected_output: .asciiz "Expected output:\nCashRulesEveryTHINGAroundMe\nObtained output:\n"
change_case_input: .asciiz "cA+SH$$$___rU*LE S^^eVE@RY~~th~ing_aRO=/[]UND_mE:|"
change_case_output: .asciiz "cA+SH$$$___rU*LE S^^eVE@RY~~th~ing_aRO=/[]UND_mE:|"

hex_digits: 
	.byte '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'

.align 2
fib_array: 
	.space	48

local_maxima_input: 
	.word 1, 3, 2, 4, 6, 5, 7, 8
local_maxima_input_size:
	.word 8

local_maxima_output: 
	.space	48

###############################################################
#                           Text Section
.text
.globl main 
.globl fib_array

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
##############################################
##############################################
test_fibonacci:
# Print part 1 information
# $v0=4 : print string, where $a0 = address of null-terminated string to print
li $v0, 4
la $a0, fibonacci_label
syscall
li $a0, 5
jal fibonacci

li $v0, 4
la $a0, fibonacci_lbl
syscall

la $s0, fib_array
li $t0, 5
begin_fib_test_print:
	blez $t0, end_fib_test_print
	li $v0, 1
	lw $a0, 0($s0)
	syscall

	sub $t0,$t0,1
	blez $t0, end_fib_test_print
	li $v0, 4
	la $a0, comma
	syscall

	addi $s0,$s0,4
	j begin_fib_test_print
end_fib_test_print:

##############################################
##############################################
test_local_maxima:
li $v0, 4
la $a0, new_line
syscall
la $a0, find_local_maxima_label
syscall

la $a0, local_maxima_input
la $a1, local_maxima_output
la $s0, local_maxima_input_size
lw $a2, 0($s0)
jal find_local_maxima

# Print output
li $v0, 4
la $a0, find_local_maxima_lbl
syscall

la $t1, local_maxima_output
la $s0, local_maxima_input_size
li $t2, 0
lw $t3, 0($s0)
print_loop:
	beq $t2, $t3, print_loop_end # check for array end
	lw $a0, ($t1) # print value at the array pointer
	li $v0, 1
	syscall
	li $v0, 4
	addi $t2, $t2, 1 # advance loop counter
	beq $t2, $t3, print_loop_end # check for array end
	la $a0, comma
	syscall
	addi $t1, $t1, 4 # advance array pointer
	j print_loop # repeat the loop
print_loop_end:

##############################################
###############################################################
# Test Change case function

li $v0, 4
la $a0, new_line
syscall
la $a0, changecase_label
syscall
# call the function
la $a0, change_case_input
la $a1, change_case_output
jal change_case
# print results
la $a0, change_case_expected_output
syscall
la $a0, change_case_output
syscall
la $a0, new_line
syscall

_end:
# end program
li $v0, 10
syscall
