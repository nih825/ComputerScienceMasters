a=[1 2 4; 2 4 3; 6 3 6];
b=[2; 5; 1];
disp('This driver shows how an error can occur when you do not do partial pivoting first elimination with partial pivoting')
gaussElim(a,b)
pause
disp('Now gaussian elimination without pivoting')
gaussElimNoPivoting(a,b)
