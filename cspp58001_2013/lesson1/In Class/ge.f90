program ge

  implicit none
  integer, parameter      :: m = 2
  real, dimension(m)      :: b
  real, dimension(m)      :: x
  real, dimension(m,m)    :: A
  integer                 :: i,j
!  A = reshape((/ 1, 2, 3, 1, 4, 6, 2, -3, -5 /), shape(A))
!  b = (/9,1,0/)
  A=reshape((/.00300, 59.14, 5.291, -6.130/),shape(A))
  b = (/59.17,46.78/);
  call upper_triangulate(A,b,m)
  do, i=1,m
     write(*,*) ( A(i,j), j=1,m )
  enddo
  print*, "b:",b


end program ge


subroutine upper_triangulate(A, b, m)
  implicit none
  integer, intent(IN)    :: m
  real, dimension(m,m)   :: A
  real, dimension(m)     :: b

  real                   :: scale
  integer                :: i,j,k

  do j=1,m
    do i = j+1,m
       if (A(i,j) /= 0) then
          scale = A(i,j)/A(j,j)
          A(i,:) = A(i,:) - A(j,:)*scale
          b(i) = b(i) - b(j)*scale
       end if
    end do
 end do

end subroutine upper_triangulate
