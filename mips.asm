.data
y: .space 4
x: .space 4
.text

lw $a1,y
sw $a1,0($sp)
addiu $sp,$sp,-4

li $s1,0
sw $s1,0($sp)
addiu $sp,$sp,-4

lw $s1,0($sp)
addiu $sp,$sp,4
lw $s2,0($sp)
addiu $sp,$sp,4
add $s3,$s1,$s2
sw $s3,0($sp)
addiu $sp,$sp,-4

lw $a1,x
sw $a1,0($sp)
addiu $sp,$sp,-4

li $s1,0
sw $s1,0($sp)
addiu $sp,$sp,-4

lw $s1,0($sp)
addiu $sp,$sp,4
lw $s2,0($sp)
addiu $sp,$sp,4
add $s3,$s1,$s2
sw $s3,0($sp)
addiu $sp,$sp,-4

lw $a1,x
sw $a1,0($sp)
addiu $sp,$sp,-4

li $s1,5
sw $s1,0($sp)
addiu $sp,$sp,-4

lw $s1,0($sp)
lw $s2,4($sp)
addiu $sp,$sp,8
slt $s3,$s1,$s2
beq $s3,$zero, L1 

li $v0,5
syscall
move $t0,$v0

sw $t0,0($sp)
addiu $sp,$sp,-4
j L2 

L1:
lw $a1,y
sw $a1,0($sp)
addiu $sp,$sp,-4

li $s1,5
sw $s1,0($sp)
addiu $sp,$sp,-4

lw $s1,0($sp)
addiu $sp,$sp,4
lw $s2,0($sp)
addiu $sp,$sp,4
add $s3,$s1,$s2
sw $s3,0($sp)
addiu $sp,$sp,-4

L2:
