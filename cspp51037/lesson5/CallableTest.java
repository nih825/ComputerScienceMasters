import java.util.*;
import java.util.concurrent.*;

public class CallableTest{
    public static void main(String[] args) throws Exception{
	Callable<String> c = new MyCallable();
	ExecutorService pool = Executors.newFixedThreadPool(3);
	Future<String> f = pool.submit(c);	
	//do intermediate work here
//	try{
//	    f.cancel(true);
//	}
//	catch(CancellationException cce){
//	    System.out.println(cce.getStackTrace());
//	    return;
//	}

	System.out.println(f.get());
	pool.shutdown();
    }




}

class MyCallable implements Callable<String>{
    public String call(){
	return("hello");
    }
    
}