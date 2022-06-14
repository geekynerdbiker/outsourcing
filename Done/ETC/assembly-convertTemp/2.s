    .data
F_temp:     .word   0
C_temp:     .word   0
Number1:    .byte   32
number2:    .byte   5
number3:    .byte   9
enterNumber:    .ascii "\nEnter a temperature in Fahrenheit: \n"
celsiusDegree:  .ascii "\nCelsius temperature is: "
array:      .word 0:25
welcome1:   .ascii " \n This program converts Fahrenheit to Celsius \n\n"

    .text
main:
    la a0, welcome1     #display welcome message
    li x0, 4
    ecall

    la x10,enterNumber             #Ask user to write a number
    li x17,4                  
    ecall                           

    la x6,array                   #store numbers array 
    li x30,25                     #maximum of 25 integers are allowed to be entered 

    # F is in x10               #(F-32) * 5 / 9
    addi x1, x0, 9      #t1 = 9
    addi x2, x2, 5      #t0 = 5
    addi s0, s0, 32     #s0 = 32
    sub x10, x6, s0     #F-32
    mul x10, x6, s0
    div t0, t1, s0
    
done:   
    la x10,celsiusDegree        #display celcius degree
    ecall 


exit:   

    ori a7, zero, 10    # define program exit system call
    ecall           # exit program