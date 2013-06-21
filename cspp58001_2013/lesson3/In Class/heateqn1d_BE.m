%a script to compute the 1d heat equation using the implicit
%backward euler method with fixed boundaries
%both direct solve and LU decomposition are used for comparison.
hold off;


nx     = 100;     % spatial grid points
nsteps = 100000;  % time steps

L      = 1;       % physical size of domain
alpha = .01       % (constant) diffusivity

dx = L/nx         % (constant) grid spacing)
dt = .001         % time step

C = alpha*dt/dx^2;% convenient constant

% create a 1-d mesh
x=linspace(0,1,nx+2)';

%Guassian initial condition
T = exp(-(5*x-2.5).^2); 
Tnew = T;

%boundary conditions
T(1) = 0; T(nx+1) = 0;  

%take a look
plot(x,T);
hold on;

%create sparse form of matrix to be solved at each timestep (see course
%notes)
A = spdiags([-C*ones(nx,1) (2*C*ones(nx,1)+ 1) -C*ones(nx,1)],[-1 0 1], nx, nx) ;


%direct solve
%for n=1:nsteps
%    b = T(2:nx+1,:);          % right hand size
%    Tnew(2:nx+1) = A\b;       % solve tridiagional for new T
%    T = Tnew;                  
%    if (~mod(n,1000))         % plot
%        plot(x,T);
%        set(gca,'YLim',[0,1]);
%        pause(.001);
%    end
%end

%more efficient: decompose first into L and U
[L U] = lu(A);

tic;
for n=1:nsteps
    b = T(2:nx+1,:);
    tmp = L\b;
    Tnew(2:nx+1) = U\tmp;
    T = Tnew;
    if (~mod(n,1000))
        plot(x,T);
        set(gca,'YLim',[0,1]);
        pause(.001);
    end
end
