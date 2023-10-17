real,allocatable:: a(:,:),b(:)
real,allocatable:: x0(:),x(:)

integer max_iter
real w
real tol

open(unit=1,file='input.txt')
open(unit=2,file='output-0.125.txt')

read(1,*,iostat=ierr)n

allocate(a(n,n),b(n),x0(n),x(n))

read(1,*)max_iter,tol

read(1,*)((a(i,j),j=1,n),i=1,n)
read(1,*)(b(i),i=1,n)
read(1,*)(x0(i),i=1,n)

read(1,*)w

call sor(a,b,n,x0,tol,w)
end
!-------------------------------------------------------------------------------
    subroutine SOR(a,b,n,x0,tol,w)
    real::a(n,n),b(n),x0(n)
    real::x(n)
    
    write(2,40)
40  format(/,"[ Result ]")
    
    k=0
    
    do
        k=k+1
        do i=1,n
            sum_x=0
            do j=1,n
                if(j<i)sum_x=sum_x+a(i,j)*x(j)
                if(j>i)sum_x=sum_x+a(i,j)*x0(j)
            end do
            x(i)=(1-w)*x0(i)+w*(b(i)-sum_x)/a(i,i)
        end do
        write(2,50)k,(x(i),i=1,n)
50      format(2x,i3,4(2x,f9.6))
        
        norm=abs(x(1)-x0(1))/abs(x(1))
        do i=2,n
            if(abs(x(i)-x0(i))/abs(x(i))>norm)norm=abs(x(i)-x0(i))/abs(x(i))
        end do
        if(norm<tol)goto 25
        
        do i=1,n
            x0(i)=x(i)
        end do
        
    end do
25  end subroutine    