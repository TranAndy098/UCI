# Q1
# Provide the MIPS assembly code segment to implement the following loop from a high-level program:
# Variable "Total" is in register $s0. Variable "i" is in $ s1 and "n" is in address 0x100010FF.
# total = 0; # Initial the total variable for sum 
# for (i = 0; i < n; i++) { 
#   total = total + i; 
# }

# add $s0, $0, $0 # total = 0
# lui $s2, 0x1000
# ori $s2, $s2, 0x10FF # address = 0x100010FF
# lw $s3, 0($s2) # n = value at 0x100010FF
# add $s1, $0, $0 # i = 0 (initializing)
# for_loop:
#     beq $s1, $s3, end # exit loop to end if i == n
#     add $s0, $s0, $s1 # total = total + i
#     addi $s1, $s1, 1 # i = i + 1
# end:

# Q2
# Implement the following high level code segments using "slt" instruction. Assume the integer variables "g" and "h" are in registers $s0 and $s1.

# Q2.1
# if(g > h)
#   g = g + h;
# else
#   g = g − h;

# slt $t0, $s1, $s0
# beq $t0, $0, h_g_e_g
# add $s0, $s0, $s1
# j end
# h_g_e_g:
# sub $s0, $s0, $s1
# end:

# Q2.2
# if (g >= h)
#   g = g + 1;
# else
#   h = h − 1;

# slt $t0, $s0, $s1
# bne $t0, $0, h_g_g
# addi $s0, $0, 1
# j end
# h_g_g:
# subi $s1, $s1, 1
# end:

# Q3
# Convert the following assembly instructions into machine code. On the left, you are given the address of each instruction.
# In your answer, please type the machine code in hexadecimal with no 0x in the front.

# Q3.1
# 0x00401000              beq $t0, $s1, Loop
# ...
# 0x0040100C    Loop:     ...
# Convert beq $t0, $s1, Loop to machine code.

# 000100 10001 01000 00 0000 0000 0000 01 -> 0001 0010 0010 1000 0000 0000 0000 0001 -> 0x12280001

# Q3.2
# 0x00401000              beq $t7, $s4, done
# ...
# 0x00402040    done:     ...
# Convert beq $t7, $s4, done to machine code.

# 000100 10100 01111 00 0001 0000 0011 11 -> 0001 0010 1000 1111 0000 0100 0000 1111 -> 0x128F040F

# Q3.3
# 0x0040310C    back:     ...
# ...
# 0x00405000              beq $t9, $s7, back
# Convert beq $t9, $s7, back to machine code.

# 000100 10111 11001 1111 10 0001 0000 10 -> 0001 0010 1111 1001 1111 1000 0100 0010 -> 0x12F9F842

# Q3.4
# 0x00403000              jal func
# ...
# 0x0041147C     func:    ...
# Convert jal func to machine code.

# 000011 0000 0100 0001 0001 0100 0111 11 -> 0000 1100 0001 0000 0100 0101 0001 1111 -> 0x0C10451F

# Q3.5
# 0x00403004    back:     ...
# ...
# 0x0040400C              j back
# Convert j back to machine code.

# 000010 0000 0100 0000 0011 0000 0000 01 -> 0000 1000 0001 0000 0000 1100 0000 0001 -> 0x08100C01
