public class Smooth1dDriver{


    public static void main(String[] args) throws Exception{
	
	boolean useNative = true;

	if (args.length < 1){
	    System.err.println("usage: Smooth nx [-native|-java]");
	    System.exit(1);
	}


	if (args.length == 2 && args[1].equalsIgnoreCase("-native"))
	    useNative = true;

	java.util.Random rn = new java.util.Random();

	int nx = Integer.parseInt(args[0]);

	double[] f  = new double[nx];

	for (int i = 0; i < nx; ++i)
	    f[i] = rn.nextDouble();
	
	double filt[] = {.5,.5,.5,.5,.5,.5,.5,.5};

	double beginTime = System.currentTimeMillis();

	if (useNative){
	    System.out.println("using native smooth method");
	    new Smooth().csmooth(f,filt);
	}
	else{
	    System.out.println("using pure java smooth method");
	    Smooth.smooth(f,filt);
	}

	double endTime = System.currentTimeMillis();
	double totalTime = (endTime - beginTime)/1.e3;
	    
	System.out.println("Total time (sec) : " + totalTime);
    }
}

