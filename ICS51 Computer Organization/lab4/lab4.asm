#                         ICS 51, Lab #4
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
#                       PART 1 (Image Thresholding)
#a0: input buffer address
#a1: output buffer address
#a2: image dimension (Image will be square sized, i.e., number of pixels = a2*a2)
#a3: threshold value 
###############################################################
threshold:
############################## Part 1: your code begins here ###


addi $sp, $sp, -20 #make space
sw $s7, 16($sp) #store t6
sw $s6, 12($sp) #store t6
sw $s5, 8($sp) #store t6
sw $ra, 4($sp) #store ra
sw $s0, 0($sp) #store sp

li $t7, 0 #r = 0
li $t6, 0 #c = 0

r_loop:
bge $t7, $a2, r_loop_exit # if r >= image dimension, exit

####### nested loop begin
c_loop:
bge $t6, $a2, c_loop_exit # if c >= image dimension, exit

mul $t5, $t7, $a2 #offset = r * columns
add $t5, $t5, $t6 #offset = r * columns + c
#mul $t4, $t5, 2 #2(byte size of each element) * offset

add $s7, $a0, $t5 #element address of input
add $s6, $a1, $t5 #element address of output

lbu $s5, ($s7) #load byte of input

if_ge: #if element value greater than or equal to threshold then make it 0xFF
blt $s5, $a3, else_l
li $s5, 0xFF
j end_treshold

else_l: #else if element value less than threshold then make it 0x00
li $s5, 0x00

end_treshold:
sb $s5, ($s6)

c_loop_end:
addi $t6, $t6, 1 #c += 1
j c_loop

c_loop_exit:

####### nested loop end

r_loop_end:
li $t6, 0 #c = 0
addi $t7, $t7, 1 #r += 1
j r_loop

r_loop_exit:


lw $s7, 16($sp) #load t6
lw $s6, 12($sp) #load t6
lw $s5, 8($sp) #load t6
lw $ra, 4($sp) #load ra
lw $s0, 0($sp) #load sp
addi $sp, $sp, 20 #make space

############################## Part 1: your code ends here ###
jr $ra

###############################################################
###############################################################
#                           PART 2 (Matrix Transform)
#a0: input buffer address
#a1: output buffer address
#a2: transform matrix address
#a3: image dimension  (Image will be square sized, i.e., number of pixels = a3*a3)
###############################################################
transform:
############################### Part 2: your code begins here ##

addi $sp, $sp, -32 #make space
sw $s7, 28($sp) #store s7
sw $s6, 24($sp) #store s6
sw $s5, 20($sp) #store s5
sw $s4, 16($sp) #store s4
sw $s3, 12($sp) #store s3
sw $s2, 8($sp) #store s2
sw $ra, 4($sp) #store ra
sw $s0, 0($sp) #store sp

li $t7, 0 #r = 0
li $t6, 0 #c = 0

t_r_loop:
bge $t7, $a3, t_r_loop_exit # if r >= image dimension, exit

####### nested loop begin
t_c_loop:
bge $t6, $a3, t_c_loop_exit # if c >= image dimension, exit

mul $t5, $t7, $a3 #offset = r * columns
add $t5, $t5, $t6 #offset = r * columns + c
#mul $t4, $t5, 2 #2(byte size of each element) * offset

add $s7, $a0, $t5 #element address of input
add $s6, $a1, $t5 #element address of output

#lbu $s5, ($s7) #load byte of input

lw $s3, ($a2) #load in M00
lw $s2, 4($a2) #load in M01
mul $s3, $s3, $t6 #M00 * x
mul $s2, $s2, $t7 #M01 * y
add $s4, $s2, $s3 #x0 =  M00 * x + M01 * y
lw $s2, 8($a2) #load in M02
add $s4, $s4, $s2 #x0 = M00 * x + M01 * y + M02

lw $s3, 12($a2) #load in M10
lw $s2, 16($a2) #load in M11
mul $s3, $s3, $t6 #M10 * x
mul $s2, $s2, $t7 #M11 * y
add $s3, $s2, $s3 #y0 =  M10 * x + M11 * y
lw $s2, 20($a2) #load in M12
add $s3, $s3, $s2 #y0 =  M10 * x + M11 * y + M12

blt $s4, 0, not_in_range
blt $s3, 0, not_in_range
bge $s4, $a3, not_in_range
bge $s3, $a3, not_in_range

mul $t5, $s3, $a3 #offset = y0 * columns
add $t5, $t5, $s4 #offset = y0 * columns + x0

add $s7, $a0, $t5 #element address of input

lbu $s5, ($s7) #load byte of input

j end_of_transform

not_in_range:
li $s5, 0

end_of_transform:
sb $s5, ($s6)


t_c_loop_end:
addi $t6, $t6, 1 #c += 1
j t_c_loop

t_c_loop_exit:

####### nested loop end

t_r_loop_end:
li $t6, 0 #c = 0
addi $t7, $t7, 1 #r += 1
j t_r_loop

t_r_loop_exit:

lw $s7, 28($sp) #load s7
lw $s6, 24($sp) #load s6
lw $s5, 20($sp) #load s5
lw $s4, 16($sp) #load s4
lw $s3, 12($sp) #load s3
lw $s2, 8($sp) #load s2
lw $ra, 4($sp) #load ra
lw $s0, 0($sp) #load sp
addi $sp, $sp, 32 #make space

############################### Part 2: your code ends here  ##
jr $ra
###############################################################
