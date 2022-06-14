A: .space 400
B: .space 400
C: .space 400

.text
        li $t0, 99   # i = 99
        la $s0, A    # load base address of A in $s0
        la $s1, B    # load base address of B in $s1
        la $s2, C    # load base address of C in $s2
while:
        ble $t0, 4, endwhile    # if i<=4, endloop
        sll $t1, $t0, 2         # $t1 = i*4
        addi $t2, $t1, -8       # $t2 = i*4 - 8
        add $t2, $t2, $s0       # add $t2 with A base address to point A[i-2]
        lw $t2, 0($t2)          # load $t2 = A[i-2]
        addi $t3, $t1, -4       # $t3 = i*4 - 4
        add $t3, $t3, $s1       # add $t3 with B base address to point B[i-1]
        lw $t3, 0($t3)          # load $t3 = B[i-1]
        add $t2, $t2, $t3       # $t2 = A[i-2] + B[i-1]
        add $t1, $t1, $s2       # calculate base address of C[i]
        sw $t2, 0($t1)          # store $t2 at C[i]
        addi $t0, $t0, -2       # decrement 2
        j while                 # loop again
endwhile:
        # system call to terminate the program
        li $v0, 10
        syscall