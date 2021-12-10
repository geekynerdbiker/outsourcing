Program p3
    integer i
    real x(1000)
    real fx(1000)
    real ans
    
    ans = 0

    do i = 0,1000
        if (sin(i*0.005) >= 0.5) then
            ans = ans + (sin(i*0.005) - 0.5) * 0.01
        endif
    end do
    
    write(*,*) ans
End Program p3