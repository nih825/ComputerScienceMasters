function [x] = matrixInverse(A)


 N = max(size(A));
A=[A eye(N)];

for j=2:N,
    for i=j:N,
        if A(j-1,j-1)==0,
        	disp('Invalid matrix');
        	return
        end
        m = A(i,j-1)/A(j-1,j-1);
        A(i,:) = A(i,:) - A(j-1,:)*m;
     end
    for k=1:j-1,
    	if A(k,j)~=0,
    		m=A(k,j)/A(j,j);
    		A(k,:)=A(k,:)-A(j,:)*m;
    	end
    end
 end

for i=1:N,
	A(i,:)=A(i,:)/A(i,i);
end

x=A(:,N+1:2*N);

