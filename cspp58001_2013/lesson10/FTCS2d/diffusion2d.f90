! diffusion2D.f90 --- FORTRAN90 version of the 2D explicit
! heat equation solver.

! Assume mesh grid is discretized by dx in both directions

program heat_diffusion
  implicit none
  real, parameter :: lx = 10., ly = lx ! length of each side
  integer, parameter :: nx = 128, ny = nx ! number of grid points in each direction
! T and Told (T at previous iteration) are the datastructures that need to be
! decomposed across processors -- they represent the 'image' in our in-class example
! each processor will work on a sub-chunk of the T and Told arrays
  real, dimension(0:nx+1,0:ny+1) :: T, Told
  real, dimension(0:nx+1,0:ny+1) :: S
  real :: alpha, dt, dx, dy, const
  integer :: i, j, iter, max_iter,nprint,file_counter
  integer*4 timei(3), timef(3) ! hours, minutes, seconds
  
 !understand dx,dy,alpha,dt,and const isn't necessary for parallelizing the code
!they simply appear in the local operator formula (I can explain if interested)
  dx = lx/nx
  dy = dx

  call itime(timei)    
  alpha = 1.0
  dt = .0001
  const = alpha*dt/dx**2
  max_iter = 100000

  file_counter = 0
  nprint = 5000

! initialize T with some data. a 2d guassian is a nice choice.
! in parallel you will have to make sure that each proc gets
! the correct chunk of T
  call init(Told,nx,ny,lx,ly)
  call init_src(S,nx,ny);
  call write_file(S,nx,ny,'src',file_counter,'.bin')
!  call write_file(Told,nx,ny,'data',file_counter,'.bin')
  file_counter = file_counter + 1

!copy T into Told (loop implied in fortran)
  do iter = 1,max_iter
     print*, iter

     do i=1,nx
        do j = 1,ny
           T(i,j) = Told(i,j) + const *                       &
                ( T(i+1,j) + T(i-1,j) + T(i,j+1) + T(i,j-1)   &
                - 4.*T(i,j)) + S(i,j)*dt
        end do
     end do
     Told = T
     if (mod(iter,nprint) == 0) then
        call write_file(T,nx,ny,'data',file_counter,'.bin')
        file_counter=file_counter+1
     end if
     
  end do

  call itime(timef)
  write(6,*) "Runtime: ", (timef(1)-timei(1) + timef(2)-timei(2) + timef(3)-timei(3))

end program heat_diffusion

subroutine write_file(T,nx,ny,base,iprint,ext)
  implicit none
  real,dimension(0:nx+1,0:ny+1) :: T
  integer          :: nx,ny
  character(len=*) :: base, ext
  integer          :: iprint
  character(100)   :: filename
  character(3)     :: cip


  if (iprint.lt.10) then
     write(cip,'(''00'',i1)')iprint
  else if (iprint.lt.100) then
     write(cip,'(''0'',i2)')iprint
  else
     write(cip,'(i3)')iprint
  endif
  filename= trim(base)//cip//ext
  print*, 'writing file: ',filename
  open(unit=22,file=filename, form='unformatted',status='unknown')
  write(22) T(:,:)
  close(22)

end subroutine write_file

subroutine init_src(S,nx,ny)
  implicit none
  integer :: nx, ny
  real, dimension(0:nx+1,0:ny+1) ::S
  integer :: midx, midy, i, j
  real :: lx,ly, x, y
  real :: dx,dy

!  midx = nx/2;
!  midy = ny/2;
  S(midx,midy) = 100.

!  S(midx-10:midx+10,midy-10:midy+10) = 100.0
! This initializes a 2D Gaussian Distribution
!  do i = 1,nx
!     x = -lx/2 + dx*i
!     do j = 1,ny
!        y = -ly/2 + dy*j
!        S(i,j) = exp(-((x-4.0)**2 + (y-4.0)**2)/.2)
!     end do
!  end do
  
end subroutine init_src


subroutine init(T, nx, ny, lx, ly)
  implicit none
  real, dimension(0:nx+1,0:ny+1) :: T
  real :: lx,ly, x, y
  integer :: nx,ny
  real :: dx,dy
  integer :: i, j
  dx = lx/nx
  dy = ly/ny
  
! This initializes a 2D Gaussian Distribution
  do i = 1,nx
     x = -lx/2 + dx*i
     do j = 1,ny
        y = -ly/2 + dy*j
        T(i,j) = exp(-((x-0.0)**2 + (y-0.0)**2)/2.)
     end do
  end do

! set boundaries to zero
  T(:,0) = 0.
  T(0,:) = 0.
  T(nx+1,:) = 0.
  T(:,ny+1) = 0.

end subroutine init
