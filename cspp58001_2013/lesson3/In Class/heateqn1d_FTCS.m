%a script to solve the 1d heat equation using
%explicit timestepping and centered differencing
hold off;
axis manual;
axis([0 1 0 1]);

nx     = 1000;
L      = 1;
nsteps = 100000;
alpha = .001 

dx = L/nx          
dt = .0005  

C = alpha*dt/dx^2;

x=linspace(0,1,nx+2);

T = exp(-(5*(x-0.5)).^2); %initial condition
Tnew = T;

T(1) = 0; T(nx+1) = 0;  %boundary conditions
plot(x,T);

for n=1:nsteps
    n
%    scalar way
%    for i=2:nx
%        Tnew(i) = T(i) + C*(T(i+1)-2*T(i)+T(i-1));
%    end
%much faster in matlab
    Tnew = T + C*(circshift(T,[0 -1]) - 2*T + circshift(T,[0 +1]));
%even better Tnew = T + C*del2(T);
    Tnew(1) = 0; Tnew(nx+1) = 0;  %boundary conditions
    if (~mod(n,1000))
        axis([0 1 0 1]);
        plot(x,T);
        set(gca,'YLim',[0,1]);
        pause(.001);
    end
    T = Tnew;
end
