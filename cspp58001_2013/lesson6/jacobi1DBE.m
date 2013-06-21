%use jacobi iteration to solve 1-d backward euler diffusion equation
% x(k+1) = (I-inv(D))*x(k) + inv(D)*b
%
%
   hold off;
dt=1.e-1;
alpha = 1;
n=175;
dx = 4/n;

C = alpha*dt/dx^2
c1 = -C*ones(n,1);
c2 = (2*C+1)*ones(n,1);

A=spdiags([c1 c2 c1],-1:1,n,n);
D = diag(diag(A));
invD = diag(1./diag(D));
B = eye(n) - invD*A;
z=linspace(-2,2,n);

MAX_ITER=1000;
nsteps = 10000;
xold = exp(-2*z.^2);
threshhold = 1.e-4;

for i=1:nsteps
	x = xold;
    niter=0;
    for j=1:MAX_ITER
        xnew = (B*x' + invD*xold')';
        e = mean(abs(x-xnew))  
        if (e < threshhold)
            break
        end
        x = xnew;
    end
    if (j == MAX_ITER)
        sprintf('%s\n','WARNING: iteration failed to converge')
    end
	sprintf('iterations: %d\n, error: %f\n', j,mean(x-xnew))
    if (i==1)
        hold on;
    end
    plot(z,x);
drawnow;
xold=x;
end
