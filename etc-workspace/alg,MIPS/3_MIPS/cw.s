.data
prompt: .asciiz "Enter the value of n: "
output_a: .asciiz "a_n = "
output_b: .asciiz "b_n = "

.text
.globl main

main:
    la $a0, prompt
    li $v0, 4
    syscall

    li $v0, 5              # read integer value of n
    syscall
    move $t0, $v0          # save n in $t0

    li $a0, 2              # set a_1 to 2
    li $a1, 1              # set b_1 to 1
    jal calc_sequence      # calculate a_n and b_n

    la $a0, output_a         # print results
    li $v0, 4
    syscall

    # move $a0, $v0          # print a_n
    li $v0, 1
    syscall

    la $a0, output_b       # print results
    li $v0, 4
    syscall

    # move $a0, $v1          # print b_n
    li $v0, 1
    syscall

    li $v0, 10             # exit program
    syscall

calc_sequence:
    subu $sp, $sp, 8       # allocate stack space
    sw $ra, 4($sp)         # save return address

    # base case
    beq $t0, 0, set_zero   # if n == 0, set a_n and b_n to 0

    beq $t0, 1, set_one    # if n == 1, set a_n and b_n to 2 and 1

    # recursive case
    addi $t0, $t0, -1      # calculate a_{n-1}
    jal calc_sequence

    add $a0, $v0, $v1      # calculate a_n = a_{n-1} + 2*b_{n-1}
    sll $a0, $a0, 1

    addi $t0, $t0, 1       # calculate b_{n-1}
    jal calc_sequence

    sub $a1, $v0, $v1      # calculate b_n = a_{n-1} - b_{n-1}

    # return values
    lw $ra, 4($sp)         # restore return address
    addu $sp, $sp, 8       # deallocate stack space
    jr $ra

set_zero:
    li $v0, 0
    li $v1, 0
    jr $ra

set_one:
    li $v0, 2
    li $v1, 1
    jr $ra