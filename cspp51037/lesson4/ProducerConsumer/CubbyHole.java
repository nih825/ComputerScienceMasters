//new CubbyHole is built off of an ArrayBlockingQueue
import java.util.concurrent.ArrayBlockingQueue;
public class CubbyHole{
    private int sz;
    private ArrayBlockingQueue<Integer> contents;
    CubbyHole(){
	this(1);
    }

    CubbyHole(int size){
	this.sz = size;
	contents = new ArrayBlockingQueue<Integer>(size);
    }

    public int get(){
	int value = 0;
	try{
	    value = contents.take();
	}
	catch(InterruptedException ie){}
	return(value);
    }

    public void put(int i){
	try{
	    contents.put(i);
	}
	catch(InterruptedException ie){}
	return;
    }
}