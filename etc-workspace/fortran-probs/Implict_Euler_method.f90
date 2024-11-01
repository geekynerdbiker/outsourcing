program Implict_Euler_method
implicit none

real, dimension (20)::x,y
integer::i
real :: c,ce,a,h
read(*,*) c,ce,a,h

x(1)=c
y(1)=ce
print*,"t=", 0.000,"for C=",x(1),"for Ce=",y(1)

i=2

do
y(i)=y(i-1)+a*((0.01)**2)
x(i)=y(i-1)+(1.001)*(ABS(y(i-1)-x(i-1)))
x(i)=x(i-1)+(1.001)*(ABS(y(i-1)-x(i-1)))
if (i == 100) exit

print*,"t=", (i-1)*0.001,"for C=",x(i),"for Ce=",y(i)
i=i+1

enddo
end