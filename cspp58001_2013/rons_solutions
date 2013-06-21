nx     = 100;
L      = 1;
nsteps = 100000;
alpha = .001 

dx = L/nx          
dt = .0005  

C = alpha*dt/dx^2;

xx=linspace(0,1,nx+2);
yy=linspace(0,1,nx+2);
[x y] = meshgrid(xx,yy);

T = exp(-(5*x-2.5).^2).*exp(-(5*y-2.5).^2); %initial condition
Tnew = T;

T(1,:) = 0; T(nx+1,:) = 0;  %boundary conditions
T(:,1) = 0; T(:,nx+1) = 0;
imagesc(T);

 for n=1:nsteps
     n
     Tnew = T + C*( circshift(T,[0 -1]) + circshift(T,[0 +1]) + ...
              +     circshift(T,[-1 0]) + circshift(T,[+1 0]) + ...
              -     4*T);
     T(1,:) = 0; T(nx+1,:) = 0;  %boundary conditions
     T(:,1) = 0; T(:,nx+1) = 0;
     if (~mod(n,1000))
         imagesc(T);
         set(gca,'ZLim',[0,1]);
         pause(.001);
     end
     T = Tnew;
 end