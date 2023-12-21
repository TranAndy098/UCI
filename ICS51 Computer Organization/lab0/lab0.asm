.text

###############################################################
###############################################################
###############################################################
#                            Part 1 (Increment Function)
# 
inc_fnt:
############################## Part 1: your code begins here ###
### (Just uncomment the following instructions)

## sum
move $t0, $0
## range
move $t1, $a0

inc_loop:
add $t0, $t0, $t1
addi $t1, $t1, -1
bgt $t1, 0, inc_loop # repeat if $t1 is bigger than 0

move $v0, $t0

############################## Part 1: your code ends here   ###
jr $ra


###############################################################
###############################################################
###############################################################
#                            Part 2 (Print int2binary Function)
# Print an integer in binary representation
print_int2bin_fnt:
############################## Part 2: your code begins here ###
### (Just uncomment the following instructions)

li $v0, 35
syscall

############################## Part 2: your code ends here   ###
jr $ra
