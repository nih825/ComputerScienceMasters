import java.util.concurrent.ArrayBlockingQueue;
public class CubbyHole {
    private ArrayBlockingQueue<Integer> contents = new ArrayBlockingQueue<Integer>(1);

    private boolean available = false;

    public int get() {
	int value=0;

	try{
	    value = contents.take().intValue();
	}
	catch(InterruptedException ie){

	}
	finally{
	    return value;
	}
    }

    public void put(int i){
	try{
	    contents.put(i);
	}
	catch(InterruptedException ie){}

	return;
    }

}
