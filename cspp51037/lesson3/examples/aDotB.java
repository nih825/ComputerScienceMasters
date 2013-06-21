public class aDotB{
    public static void main(String[] args){
	int N = Integer.parseInt(args[0]);
	float a[] = new float[N];
	float b[] = new float[N];
	float dp = 0.0f;
	//some intialization
	for (int i = 0; i < N; ++i){
	    a[i] = (float) (i % 10);
	    b[i] = (float) (i % 10);
	}

	long ts = System.currentTimeMillis();
	//compute the dot product
	for (int iter=0; iter<10; ++iter){
	    for (int i = 0; i < N; ++i)
		dp += a[i]*b[i];
	}
	long te = System.currentTimeMillis();
	System.out.println("total time: " +  (te-ts)/1000.);
    }


}