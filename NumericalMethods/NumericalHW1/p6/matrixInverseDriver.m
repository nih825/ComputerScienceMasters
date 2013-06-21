disp('This simple driver tests my matrix inverse method against the matlab matrix inverse method')

a=[1 2 4; 4 6 3; 2 8 5]
disp('First find inverse of a using built in matlab method')
inv(a)
disp('Next are the results using my method')
matrixInverse(a)
disp('Hooray, they are the same, feel free to try with other non singular matrices')