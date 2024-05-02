Program p4
    integer npts
    real, allocatable, dimension(:) :: xx, yy, zz
    real xf, yf, zf, xin, yin, zin, dd
    read *, xf, yf, zf
    
    open(unit=10, file="ship_pts.dat")
    read(10,*) npts
    
    allocate(xx(n),yy(n),zz(n))
    dmin = 999999
    dd = 0

    do ii = 1,npts
        read(10,*) xx(ii), yy(ii), zz(ii)
        xin = xx(ii)
        yin = yy(ii)
        zin = zz(ii)
        
        call get_dist(xin, yin, zin, xf, yf, zf, dd)
        if(dd < dmin) dmin = dd
    end do
    
    close(10)
    write(*,*) dmin
End Program p4

subroutine get_dist(xin, yin, zin, xf, yf, zf, dd)
    dd = sqrt((xin-xf)**2+(yin-yf)**2+(zin-zf)**2)
    return
end subroutine get_dist
