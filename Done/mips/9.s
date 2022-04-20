.data
arr: .word 7, 5, 6, 1, 4
space: .asciiz " "
.text
main:
la $s1, arr
li $s2, 5
move $t0, $s2
main_loop:
beqz $t0, print
li $t1, 0
move $t2, $s1
jal bubble_sort
sub $t0, $t0, 1
j main_loop
bubble_sort:
beq $t1, $t0, jumpra
lw $t3, 0($t2)
lw $t4, 4($t2)
slt $t5, $t4, $t3
bnez $t5, swap
addi $t2, $t2, 4
addi $t1, $t1, 1
j bubble_sort
jumpra:
jr $ra
swap:
sw $t3, 4($t2)
sw $t4, 0($t2)
addi $t2, $t2, 4
addi $t1, $t1, 1
j bubble_sort
print:
beqz $s2, exit
lw $t0, 0($s1)
move $a0, $t0
li $v0, 1
syscall
la $a0, space
li $v0, 4
syscall
addi $s1, $s1, 4
sub $s2, $s2, 1
j print
exit:
li $v0, 10
syscall
