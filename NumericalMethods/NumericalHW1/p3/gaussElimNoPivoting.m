function [x] = gaussElimNoPivoting(A,b)
% File gaussElim.m
%   This subroutine will perform Gaussian elmination
%   on the matrix that you pass to it.
%   i.e., given A and b it can be used to find x,
%        Ax = b
%
%   To run this file you will need to specify several
%   things:
%   A - matrix for the left hand side.
%   b - vector for the right hand side
%
%   The routine will return the vector x.
%   ex: [x] = gaussElim(A,b)
%     this will perform Gaussian elminiation to find x.
%
% Note that this is a naive proof-of-principle solver --
% no pivoting is performed, /input checks, etc.


 N = max(size(A));

% Perform Gaussian Elimination
for j=2:N,
     % First swap rows to have greatest value as the pivot
    	

	%Now do standard procedure
     for i=j:N,
        if A(j-1,j-1)==0,
        	disp('Invalid matrix');
        	return
        end
        m = A(i,j-1)/A(j-1,j-1);
        A(i,:) = A(i,:) - A(j-1,:)*m;
        b(i) = b(i) - m*b(j-1);
     end
 end

%Check if any rows are all zero leading to a singular matrix
for i=1:N,
	anynonzeros=0;
	for j=1:N,
		if A(i,j)~=0,
			anynonzeros=1;
		end
	end
	if anynonzeros==0,
		disp('Error Matrix is not full rank')
		return
	end
end	

% Perform back substitution

 x = zeros(N,1);
 x(N) = b(N)/A(N,N);

 for j=N-1:-1:1,
   x(j) = (b(j)-A(j,j+1:N)*x(j+1:N))/A(j,j);
 end


