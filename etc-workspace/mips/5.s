swap: sll $t1, $a1, 2
add $t1, $a0, $t1

lw $t0, 0($t1)
lw $t2, 4($t0)

lw $t2, 0($t1)
lw $t0, 4($t0)
