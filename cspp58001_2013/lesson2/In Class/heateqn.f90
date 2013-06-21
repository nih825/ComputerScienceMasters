program heateqn
  implicit none
  integer :: i,n
  integer, parameter :: nx = 1000
  integer, parameter :: nsteps = 1000
  real :: alpha, L, dx, dt
  real, dimension(0:nx+1) :: Told, Tnew
  
  !zero boundary conditions
  Told(0) = 0.
  Told(nx+1) = 0.
  
  L = 1.0
  alpha = 1.0
  dx = L/nx
  dt = .000001
  
  call init(Told, nx, L)

  write(*,*) Told
  stop

  !for (i=0;i<=nsteps;++i)
  do n=1,nsteps
     print*, n
     do i=1,nx
        Tnew(i) = Told(i) + dt*alpha/(dx*dx)*(Told(i-1) - &
             2*Told(i) + Told(i+1))
     end do
     Told(:) = Tnew(:)
  end do
  
  write(*,*) Tnew

end program heateqn

subroutine init(T, nx, L)
  real, dimension(0:nx+1) :: T
  integer :: nx, L

  real :: dx, x
  integer :: i

  dx = 10./nx
  x = -5.0
  do i=1,nx
     T(i) = exp(-x*x/2.)
     x = x + dx
  end do
  T(0) = 0.
  T(nx+1) = 0.
end subroutine init
