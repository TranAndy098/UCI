#                         ICS 51, Lab #3
#
#      IMPORTANT NOTES:
#
#      Write your assembly code only in the marked blocks.
#
#      DO NOT change anything outside the marked blocks.
#
###############################################################
#                           Text Section
.text

###############################################################
###############################################################
###############################################################
#                           PART 1 (fib_recur)
# $a0: input number
###############################################################
fib_recur:
############################### Part 1: your code begins here ##

addi $sp, $sp, -12 #make space
sw $t6, 8($sp) #store t6
sw $ra, 4($sp) #store ra
sw $s0, 0($sp) #store sp

#if n <= 1
addi $t7, $0, 1 #make variable to check if n is less than or equal to 1
bgt $a0, $t7, fib_recur_else #if n is greater than 1 then branch to else
addi $v0, $a0, 0 #return n
j fib_recur_end

#else:
fib_recur_else:
move $s0, $a0 #save n to s0
addi $a0, $s0, -1 #n = n - 1
jal fib_recur #fib_recur(n-1)
addi $t6, $v0, 0 #t6 = fib_recur(n-1)
addi $a0, $s0, -2 #n = n - 2
jal fib_recur #fib_recur(n-2)
add $v0, $v0, $t6 #fib_recur(n-2) + fib_recur(n-1)

fib_recur_end:
lw $t6, 8($sp) #load t6
lw $ra, 4($sp) #load ra
lw $s0, 0($sp) #load sp
addi $sp, $sp, 12 #free space

############################### Part 1: your code ends here  ##
jr $ra

###############################################################
###############################################################
###############################################################
#                           PART 2 (catalan_recur)
# $a0: input number
###############################################################
catalan_recur:
############################### Part 2: your code begins here ##

addi $sp, $sp, -24 #make space
sw $t3, 20($sp) #store t3
sw $t4, 16($sp) #store t4
sw $t5, 12($sp) #store t5
sw $t6, 8($sp) #store t6
sw $ra, 4($sp) #store ra
sw $s0, 0($sp) #store sp

#if n <= 1
addi $t7, $0, 1 #make variable to check if n is less than or equal to 1
bgt $a0, $t7, catalan_recur_else #if n is greater than 1 then branch to else
addi $v0, $0, 1 #return 1
j catalan_recur_end

catalan_recur_else:
move $s0, $a0 #save n to s0

addi $t3, $0, 0 #res = 0

addi $t4, $0, 0 #i = 0
addi $t5, $a0, 0 #n

catalan_recur_loop:
bge $t4, $t5, catalan_recur_loop_end # if i >= n, then branch else loop
addi $a0, $s0, -1 #n = n - 1
sub $a0, $a0, $t4 #n = n - 1 - i
jal catalan_recur #catalan_recur(n-i-1)
move $t6, $v0 #t6 = catalan_recur(n-i-1)


move $a0, $t4 #move i to recursive call with
jal catalan_recur #catalan_recur(i)
mul $t6, $v0, $t6 #catalan_recur(i) * catalan_recur(n-i-1)

add $t3, $t3, $t6 #res += catalan_recur(i) * catalan_recur(n-i-1)

addi $t4, $t4, 1 #i += 1
j catalan_recur_loop

catalan_recur_loop_end:
addi $v0, $t3, 0 #return res

catalan_recur_end:
lw $t3, 20($sp) #load t3
lw $t4, 16($sp) #load t4
lw $t5, 12($sp) #load t5
lw $t6, 8($sp) #load t6
lw $ra, 4($sp) #load ra
lw $s0, 0($sp) #load sp
addi $sp, $sp, 24 #free space

############################### Part 2: your code ends here  ##
jr $ra

###############################################################
###############################################################
###############################################################
#                           PART 3A (SYSCALL: file read, ASCII to Integer)
#
# $a0: the address of the string that represents the input file name
# $a1: the base address of an integer array that will be used to store distances
# data_buffer : the buffer that you use to hold data for file read (MAXIMUM: 300 bytes)
load_pts_file:
############################### Part 3A: your code begins here ##

move $t8, $a1 #moving address to write into

li   $v0, 13       # system call for open file
# a0 is already ready for file name
li   $a1, 0        # Open for reading (flags are 0: read, 1: write)
li   $a2, 0        # mode is ignored
syscall            # open a file (file descriptor returned in $v0)
move $t0, $v0      # save the file descriptor 

li   $v0, 14       # system call for read file
move $a0, $t0      # file descriptor 
la   $a1, data_buffer   # address of buffer from which to read
li   $a2, 300       # max hardcoded buffer length
syscall            # read file


#my code below

li $t1, 0 #loop counter
li $t2, 0 #counter for distances calculated
la $t3, data_buffer #address for current character

li $t5, 0 #previous number = 0
li $t6, 0 #current number = 0


load_pts_file_loop: #loop to iterate through points

bge $t1, $v0, load_pts_file_end #if number of iterations has matched number of characters from file
lb $t7, ($t3) #load character

load_pts_file_if_negative: #if negative, then get next character and make that negative
bne $t7, 45, load_pts_file_if_space
addi $t1, $t1, 1 #increment "loop" counter
addi $t3, $t3, 1 #increment address to get next number
lb $t7, ($t3) # get number
subi $t6, $t7, 0x30 #subtract 0x30 to get digit
mul $t6, $t6, -1 #multiply by -1 because original t7 was 0x2D which is "-"
j load_pts_file_loop_end


load_pts_file_if_space: #if space, then make current value the previous value
bne $t7, 32, load_pts_file_if_newline
move $t5, $t6 #makes t5 the current value t6
li $t6, 0 #makes t6 = 0 to get ready for new number
j load_pts_file_loop_end


load_pts_file_if_newline: #if newline, then calculate distance between t6 and t5 and increment distances counter
bne $t7, 10, load_pts_file_loop_else

bge $t5, $t6, t5_greater_than_t6
t6_greater_than_t5:
sub $t7, $t6, $t5
j distance_calculated

t5_greater_than_t6:
sub $t7, $t5, $t6
j distance_calculated

distance_calculated:
mul $t6, $t2, 4
add $t6, $t6, $t8
sw $t7, ($t6) #store distance in dist_array

li $t6, 0 #reset t6
li $t5, 0 #reset t5

addi $t2, $t2, 1 #increment distance counter

j load_pts_file_loop_end


load_pts_file_loop_else: #else means it is character of a number, if it is then multiple current t6 by 10 and add t7

subi $t7, $t7, 0x30 #subtract 0x30 to get digit
mul $t6, $t6, 10 #shifts current number t6 over in base 10
bltz $t6, load_pts_file_loop_else_negative #if current number t6 is less than 0, then we need subtract instead of add

load_pts_file_loop_else_positive:
add $t6, $t6, $t7
j load_pts_file_loop_end

load_pts_file_loop_else_negative:
sub $t6, $t6, $t7
j load_pts_file_loop_end

load_pts_file_loop_end:
addi $t1, $t1, 1 #increment loop counter
addi $t3, $t3, 1 #increment character
j load_pts_file_loop

load_pts_file_end:

li $v0, 16 # close file
move $a0, $t0 # file descrip to close
syscall

move $a1, $t8
move $v0, $t2

############################### Part 3A: your code ends here   ##
jr $ra

###############################################################
###############################################################
###############################################################
#                           PART 3B (SYSCALL: file write, Integer to ASCII)
#
# $a0: the address of the string that represents the output file name
# $a1: the base address of an integer array that stores distances
# $a2: the number of valid distances to the integer array
# data_buffer : the buffer that you use to hold data for file read (MAXIMUM: 300 bytes)
save_dist_list:
############################### Part 3B: your code begins here ##

addi $sp, $sp, -8 #move sp down to store ra, sp
sw $ra, 0($sp)
sw $s0, 4($sp)

move $t0, $a0
move $t1, $a1
#move $t2, $a2
la $t3, data_buffer

#read from array
#lw $a0, ($a1)
#addi $a1, $a1, 4

#writing to buffer
#li $t7, 0x37
#sb $t7, ($t3)
#addi $t3, $t3, 1


#for loop to go through integer array
li $t4, 0 # loop counter

li $t7, 10 #constant
li $t8, 0 # character counter


for_loop:
bge $t4, $a2, for_loop_end
lw $t5, ($a1) #load integer
jal int_to_str #call the int_to_str recusrsive function to turn int into string and add to buffer
li $t5, 0x0A
sb $t5, ($t3) #store a newline
addi $t8, $t8, 1
addi $t3, $t3, 1 #go to next character address
addi $a1, $a1, 4 #move to next address to read
addi $t4, $t4, 1 #increment loop counter
j for_loop

for_loop_end:
j file_writing


#int_to_str recursive function to add charcters to buffer
int_to_str:

#prologue
addi $sp, $sp, -16 #move sp down to store ra, sp, t5
sw $ra, 0($sp)
sw $s0, 4($sp)
sw $t5, 8($sp)
sw $t2, 12($sp)

#if n < 10 then store digit as character
bge $t5, $t7, int_to_str_else
addi $t5, $t5, 0x30 #turning into character
sb $t5, ($t3) #store it in buffer
addi $t8, $t8, 1
addi $t3, $t3, 1 #move to next slot
j int_to_str_end

#else means number needs to be decomposed
int_to_str_else:
div $t5, $t7 #t5 divide by 10, its t5//10 in hi and t5%10 in lo
mflo $t5 #t5//10
mfhi $t2 #t5%10
jal int_to_str #int_to_str(n//10)
move $t5, $t2
jal int_to_str #int_to_str(n%10)
j int_to_str_end

int_to_str_end:
#epilogue
lw $ra, 0($sp)
lw $s0, 4($sp)
lw $t5, 8($sp)
lw $t2, 12($sp)
addi $sp, $sp, 16 #free up space that stored ra, sp, t5

jr $ra



file_writing:
#open file for writing that does not exist
li $v0, 13 #system call for open file
move $a0, $t0
li $a1, 1 #open for writing
li $a2, 0 #mode is ignored
syscall #open a file

move $t6, $v0 #save the file descriptor


#write to file
li $v0, 15 #system call for write to file
move $a0, $t6 #file descriptor
la $a1, data_buffer #address of buffer from which to write
move $a2, $t8 #hardcoded buffer length
syscall #write to file


#close the file
li $v0, 16 #system call for close file
move $a0, $t6 #file descriptor to close
syscall #close file

lw $ra, 0($sp)
lw $s0, 4($sp)
addi $sp, $sp, 8 #move sp down to store ra, sp

############################### Part 3B: your code ends here   ##
jr $ra