li $s0, 0x10010000

li $s1, 0x04030201
sw $s1, ($s0)

li $s1, 0x02010605
sw $s1, 4($s0)

li $s1, 0x00050403
sw $s1, 8($s0)

addi $a0, $s0, 0
addi $a1, $s0, 6
addi $a2, $s0, 9
li $t0, 4
li $t1, 3
li $t2, 0
li $t3, 0
li $t9, 0






sub $t4, $t0, $t1
addi $t4, $t4, 1
outerloop:
beq $t2, $t4, end

add $t5, $a0, $t2
lb $t6, ($t5)
add $t8, $a1, $0
lb $t7, ($t8)
mul $t6, $t6, $t7
add $t9, $t9, $t6

addi $t5, $t5, 1
lb $t6, ($t5)
addi $t8, $t8, 1
lb $t7, ($t8)
mul $t6, $t6, $t7
add $t9, $t9, $t6

add $t6, $t2, $a2
sb $t9, ($t6)

addi $a0, $a0, 1
addi $t9, $0, 0
addi $t2, $t2, 1
j outerloop
end: