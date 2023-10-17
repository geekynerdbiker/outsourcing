.data
a1: .word 4, 1, 5, 2, 0, 0
.text
main:
la $s0, a1
li $s1, 4

move $t0, $s0

add $s2, 0($t0), 1($t0)
add $s3, 2($t0), 3($t0)

move 4($t0), $s2
move 5($t0), $s3

li $v0, 1
syscall

li $v0, 10
syscall
