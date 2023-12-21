li $t0, 2
sll $t0, $t0, 2
addi $t0, $t0, 1
addi $t1, $zero, 3
div $t0, $t1
mflo $t0
ori $t2, $t0, 8