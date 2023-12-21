#1, Write a MIPS program that divides the content of register $s0 by 8 using only bit shift.
li $s0, 64
srl $s0, $s0, 3

#-----------------------------------------------------------------------------------------------------------------------------------------------------
#2, Write a program to check if the content of the register $s0 is even or odd using sll or srl only.
li $s0, 32
srl $s1, $s0, 1
sll $s1, $s1, 1

#if s1 == s0, then s0 is even, if not then s0 is odd


srl $s1, $s0, 1
sll $s1, $s1, 1
beq $s0, $s1, even
odd:
li $v0, 1
j end

even:
li $v0, 0
j end

end:
#if $v0 has a 0 then $s0 is even, but if it has a 1 then $s0 is odd

#-----------------------------------------------------------------------------------------------------------------------------------------------------
#3, For the following assembly pseudo code, write the assembly instructions using ori and lui instructions:
# addi $s0, $s2, OxFE32148A

li $s2, 0x00112233

lui $s1, 0xFE32
ori $s1, $s1, 0x148A
add $s0, $s2, $s1

#-----------------------------------------------------------------------------------------------------------------------------------------------------
#4, Write a MIPS program that multiplies the content of register $s1 by 10 using only shift operations and add operation.
li $s1, 10
sll $t2, $s1, 3
sll $t3, $s1, 1
add $s1, $t2, $t3

#-----------------------------------------------------------------------------------------------------------------------------------------------------
#5, The content of a part of MIPS memory and the contents of three registers are provided below. Answer the following questions?

addi $s0, $s0, 0x10010003
addi $s1, $s1, 0x10010009
addi $s2, $s2, 0x10010004

li $t0, 0xef002476
li $t2, 0x10010000
sw $t0, 0($t2)

li $t0, 0x54000231
addi $t2, $t2, 4
sw $t0, 0($t2)

li $t0, 0xeff17761
addi $t2, $t2, 4
sw $t0, 0($t2)

li $t0, 0x04c76581
addi $t2, $t2, 4
sw $t0, 0($t2)

#5.1 lw $s0, 4($0)
#What’s the content of $s0 in hex?'
li $t1, 0x10010000
lw $s0, 4($t1)
#54000231

#5.2 lb $s1, 5($s2)
#What’s the content of $s1 in hex?
lb $s1, 5($s2)
#00000077

#5.3 lbu $s2, 5($s2)
#What’s the content of $s2 in hex?
lbu $s2, 5($s2)
#00000077

#-----------------------------------------------------------------------------------------------------------------------------------------------------
#6, Write MIPS assembly instructions for the following code:
#x = 5;
#int y= 5 * x * x + 2 * x + 3
#Assume register $t0 represents variable x and register $t1 represents variable y.
li $t0, 5 #x
li $s2, 5 #x^2 coeffeient
mult $t0, $t0
mflo $t1 #x^2
mult $t1, $s2
mflo $t1 #5x^2
sll $t4, $t0, 1 #2x
add $t1, $t1, $t4 #5x^2 + 2x
addi $t1, $t1, 3 #5x^2 + 2x + 3
