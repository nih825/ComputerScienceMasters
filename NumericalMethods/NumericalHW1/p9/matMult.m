
builtInMultiplierTime=zeros(1,5);
loopIndexingTime=zeros(1,5);
matrixSizes=[100 250 500 750 1000];

for p=1:5
	A=ones(matrixSizes(p),matrixSizes(p));
	B=ones(matrixSizes(p),matrixSizes(p));
	start=cputime;
	A*B;
	builtInMultiplierTime(p)=cputime-start;

	Result=zeros(matrixSizes(p),matrixSizes(p));
	start=cputime;
	for i=1:matrixSizes(p)
		for j=1:matrixSizes(p)
			for k=1:matrixSizes(p)
				Result(i,j)=Result(i,j) + A(i,k) * B(k,j);
			end
		end	
	end	
	loopIndexingTime(p)=cputime-start;

end
cTimes=[.002449 .019498 .306951 1.864561 11.56996]
loopIndexingTime
builtInMultiplierTime

plot(cTimes)
hold all
plot(loopIndexingTime)
plot(builtInMultiplierTime)
