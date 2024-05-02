main:
    addi $a0, $zero, 21
    addi $a1, $zero, 17
    addi $a2, $zero, 6
    jal max
    li $v0, 10
    syscall
max:
    add $v0, $a0, $zero
    sub $t0, $a1, $v0
    bltz $t0, okay
    add $v0, $a1, $zero
okay:
    sub $t0, $a2, $v0
    bltz $t0, done
    add $v0, $a2, $zero
done: jr $ra
