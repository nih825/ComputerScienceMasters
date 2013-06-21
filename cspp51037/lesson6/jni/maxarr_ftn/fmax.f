      subroutine maxval(size, arr, max)
      integer*4 size
      real*8 arr(*)
      real*8 max
      integer*4 i
      max=999.d0

      print*, "size: ", size
      max = arr(1)
      do i = 2,size
         if (arr(i) .gt. max) then 
            max = arr(i)
         end if
      end do

      
      end
