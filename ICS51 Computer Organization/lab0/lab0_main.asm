.include "lab0.asm"

.data

.text
.globl main

main:
# Calculating the sum of range [1, 6]

# Set up the range
li $a0, 6


### Call inc_fnt function
jal inc_fnt


### store the return result into $t5 after the function call
move $s0, $v0


# Print the result
li $v0, 1
move $a0, $s0
syscall

# Print a newline character
li $a0, '\n'
li $v0, 11
syscall

### Call print_int2bin_fnt function
move $a0, $s0
jal print_int2bin_fnt

# end program
li $v0, 10
syscall
