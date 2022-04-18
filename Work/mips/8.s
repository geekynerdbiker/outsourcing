leaf_example:
addi $sp, $sp, -12
sw $t1, 8($sp)
sw $t0, 4($sp)
sw $s0, 0($sp)

add $t0, $a0, $a1
add $t1, $a2, $a3

add $v0, $s0, $zero