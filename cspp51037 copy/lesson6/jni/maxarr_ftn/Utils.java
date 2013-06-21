class Utils{
    public native double max(double a, double b);
    public native double maxarr(double[] arr);
    static{
	System.loadLibrary("utils");
    }


    public static void main(String[] args){
	final int SIZE = 1000;
	double[] arr = new double[SIZE];
	for (int i=0;i<SIZE;i++){
	    arr[i] = (double) i;
	}
	Utils x = new Utils();
	System.out.println(x.max(2.2,2.3));
	System.out.println(x.maxarr( arr )); 
    }
}
