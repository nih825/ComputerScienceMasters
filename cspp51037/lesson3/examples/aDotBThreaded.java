public class aDotBThreaded{
    public static void main(String[] args){
	int N = Integer.parseInt(args[0]);
	float dp = 0.0f;
	LocalAnswer ans1 = new LocalAnswer();
	LocalAnswer ans2 = new LocalAnswer();
	//container to return partial answers
	//artificat of run not having a return value
	Thread t1 = new Thread(ans1);
	Thread t2 = new Thread(ans2);
	dp = ans1.val + ans2.val;
	//some intialization

	long ts = System.currentTimeMillis();
	
	long te = System.currentTimeMillis();
	System.out.println("total time: " +  (te-ts)/1000.);
    }

}

class WorkerThread extends Thread{
    LocalAnswer ans;
    private float dpl = 0.0f;
    float a[] = new float[N];
    float b[] = new float[N];
    public WorkerThread(LocalAnswer ans){
	this.ans = ans;
    }

    public void run(){
	int i;
	for (int i = 0; i < N; ++i){
	    a[i] = (float) (i % 10);
	    b[i] = (float) (i % 10);
	}
	//compute the dot product
	//assume two threads
	int iter = 10;
	int local_iter = iter/2;
	for (int iter=0; iter<local_iter; ++iter){
	    for (int i = 0; i < N; ++i)
		dpl += a[i]*b[i];
	}
	this.ans.val = dpl;
    }
    
}

class LocalAnswer{
    float val=0.0;
}
