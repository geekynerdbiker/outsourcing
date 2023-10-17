Program statistics
    real x(10)
    real sum, mean, var, std
    
    open(unit=10, file="Input.txt")
    
    sum=0.0
    
    do i = 1, 10
        read(10,*) x(i)
    end do
    
    sum = get_sum(x)
    mean = get_mean(sum)
    var = get_var(x, mean)
    std = get_std(var)
    close(10)
    
    open(unit=10, file="Output.txt")
    WRITE(10,*) mean
    WRITE(10,*) mean
    WRITE(10,*) std
    
End Program statistics

real FUNCTION get_sum(x)
    real x(10)
    
    do i = 1, 10
        get_sum = get_sum + x(i)
    end do
    
    return
End FUNCTION get_sum

real FUNCTION get_mean(sum)
    get_mean = sum / 10
    
    return
End FUNCTION get_mean

real FUNCTION get_var(x, mean)
    real x(10)
    real mean
    
    do i = 1, 10
        get_var = get_var + (x(i) - mean)**2
    end do
    get_var = get_var / 10
    
    return
End FUNCTION get_var

real FUNCTION get_std(var)
    get_std = var**0.5
    
    return
End FUNCTION get_std