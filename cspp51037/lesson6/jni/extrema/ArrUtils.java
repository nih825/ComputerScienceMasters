class ArrUtils{
    public static native void extrema(float[] arr, float[] ret);

    public static void findgen(float[] arr, int strt){
	for (int i = 0; i < arr.length; ++i){
	    arr[i] = strt + i;
	}
    }

    static{
	System.loadLibrary("arrutils");
    }
    
    public static void main(String[] args){
	float[] arr   = new float[100];
	float[] extrema = new float[2];
	findgen(arr,0);

	extrema(arr, extrema);

	System.out.println("min: " + extrema[0]);
	System.out.println("max: " + extrema[1]);
    }

}
