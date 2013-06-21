class Smooth{
    

    public static native void csmooth(double[][] data,
				      double[][] kernel);

    public static native void csmooth(double[] data,
				      double[] kernel);

    {
	System.out.println("trying to load library smooth ...");
	System.loadLibrary("smooth");
	System.out.println("library smooth loaded ...");
    }


    public static void smooth(double[][] data,
			      double[][] kernel){
	int nx = data.length;
	int ny = data[0].length;
	int nkx = kernel.length;
	int nky = kernel[0].length;


	for (int i = 0; i < nx - nkx; ++i){
	    for (int j = 0; j < ny - nky; ++j){
		double sval = 0;
		for (int jj = 0; jj < nky; ++jj){
		    for (int ii = 0; ii < nkx; ++ii){
			sval += data[i + ii][j + jj]*kernel[ii][jj];
		    }
		}
		data[i][j] = sval;
	    }
	}


    }

    public static void smooth(double[] data, 
			      double[] kernel){
	int nx = data.length;
	int nk = kernel.length;
	
	for (int i = 0; i < nx - nk; ++i){
	    double sval = 0;
	    for (int j = 0; j < nk; ++j){
		sval += data[j+i]*kernel[j];
	    }
	    data[i] = sval;
	}
    }
    

    private static void prArr(double[] arr){
	System.out.println("-----------");
	for (int i = 0; i < arr.length; ++i){
	    System.out.println(arr[i]);
	}
	System.out.println("-----------");
    }
	
    public static void main(String[] args) throws Exception{
	if (args.length != 2){
	    System.err.println("usage: Smooth nx ny");
	    System.exit(1);
	}

	java.util.Random rn = new java.util.Random();

	int nx = Integer.parseInt(args[0]);
	int ny = Integer.parseInt(args[1]);

	double[][] f  = new double[nx][ny];

	for (int i = 0; i < nx; ++i)
	    for (int j = 0; j < ny; ++j)
		f[i][j] = rn.nextDouble();
	
	double filt[][] = {{.5,.5},{.5,.5}};

	double beginTime = System.currentTimeMillis();

	Smooth.smooth(f,filt);

	double endTime = System.currentTimeMillis();
	double totalTime = (endTime - beginTime)/1.e3;
	    
	System.out.println("Total time (sec) : " + totalTime);
    }

}
