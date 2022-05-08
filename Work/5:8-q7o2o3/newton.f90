PROGRAM nr
integer :: i
real :: x, f, df
write(*,*) "x=?"
read (*,*)  x           
write (*,*) '# Initial value: x=',x

 do i=1,100
     f= x**4 - 6.4*(x**3) + 6.45*(x**2) + 20.538*x - 31.752
     df = 4*(x**3) - 3.0*6.4*(x**2) + 2.0*6.45*x - 20.538
     write (*,*) i,x,f,df
     x = x-f/df
 end do

 write (*,*) '#x = ',x
END PROGRAM