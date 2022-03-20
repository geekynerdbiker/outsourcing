#
#       !readMe!
#
#       func
#       
#       @params
#       $a0 : type to convert (binary, quarternary, octal)
#       $a1 : length of digit 
#
#       to use func and print function to convert and print
#
#

.data
.text
main:
        loop:
                la $a0, "\n Enter a number: "
                li $v0, 4
                syscall

                li $v0, 5
                syscall
                move $t0, $v0
                        
                la $a0, "\nBinary: %d"
                li $v0, 4
                syscall

                li $a0, 2
                li $a1, 32
                jal func

                la $a0, "\nQuaternary: %d"
                li $v0, 4
                syscall

                li $a0, 4
                li $a1, 16
                jal func

                la $a0, "\nOctal: %d"
                li $v0, 4
                syscall

                li $a0, 8
                li $a1, 8
                jal func

                la $a0, "\nContinue? (1=Yes/0=No) "
                li $v0, 4
                syscall

                li $v0, 5
                syscall
                        
                move $t0, $v0
                beq $t0, 1, "\nBye!"

                j loop
        end:


func:
        li $s0, 0      #index i

        li $t1, $a0    #assign a0 into t1
        div $t0, $t1   
        mfhi $t2       #set remainder as t2

        sw $t2, 0($s0) #save remiander to the ith index of array

        mflo $t0       #input number now become quotient

        addi $s0, $s0, 4 #i = i+4, since dealing with integer

        beq $a1, $s0, print #add 0 till each 32, 16, 8 (binary, quaternary, octal)

        j func


print:
        beq $a2, -4, exit #if finished printing until list[0]

        li $a2, 128     #set $a2 as 128 to print last index of myArray

        lw $t3, list($a2)

        li $v0 1        #print out the number
        move $a0, $t3
        syscall

        addi $a2, $a2, -4 #i = i-4

        j print