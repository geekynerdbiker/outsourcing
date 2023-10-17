.data
a1: .word 4
a2: .word 4
a3: .word 3
a4: .word 2
.text
main:
lw $t0, a1
lw $t1, a2
lw $t2, a3
lw $t3, a4

add $s0, $t0, $t1
add $s1, $s0, $t2
add $s2, $s1, $t3

move $a0, $s2
li $v0, 1
syscall

li $v0, 10
syscall
