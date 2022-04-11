Program std
    integer n
    real x(10)
    real sum, sqsum, mean, stdv
    
    open(unit=10, file="Input.txt")
    
    n=0
    sum=0.0
    sqsum=0.0
    
    do i = 1, 10
        read(10,*) x(i)
        n = n + 1
        WRITE(*,*) x(i)
    end do
    
    sum = get_sum(x)
    sqsum = get_sum(x)
    mean = get_mean(sum, n)
    stdv = get_stdv(sqsum, n, mean)
    close(10)
    
    open(unit=10, file="Output.txt")
    WRITE(10,*) sum, sqsum, stdv
    
End Program std

real FUNCTION get_sum(x)
    real x(10)
    
    do i = 1, 10
        get_sum = get_sum + x(i)
    end do
    
    return
End FUNCTION get_sum

real FUNCTION get_sqsum(xx)
    real x(10)
    
    do i = 1, 10
        get_sqsum = get_sqsum + xx(i)**2
    end do
End FUNCTION get_sqsum

real FUNCTION get_mean(mean, sum, n)
    get_mean = sum / n
    return
End FUNCTION get_mean

real FUNCTION get_stdv(sqsum, n, mean)
    get_stdv = (sqsum / n - mean**2)**0.5
    return
End FUNCTION get_stdv