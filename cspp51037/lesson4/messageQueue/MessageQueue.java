import java.util.Vector;
public class MessageQueue{
    private int MAXQUEUE;
    private Vector<String> messages;

    MessageQueue(int size){
	MAXQUEUE = size;
	messages = new Vector<String>();
    }

    //called by producer
    public synchronized void put(){
	while(messages.size() == MAXQUEUE){
	    System.out.println("queue full,waiting to drain ...");
	    try{
		wait();
	    }
	    catch(InterruptedException ie){}
	}
	messages.addElement(new java.util.Date().toString());
	notify();
    }

    //called by consumer
    public synchronized String get(){
	notify();
	while (messages.size() == 0){
	    System.out.println("queue empty, waiting to fill ...");
	    try{
		wait();
	    }
	    catch(InterruptedException ie){}
	}
	String message = messages.firstElement();
	messages.removeElement(message);
	return message;
    }

    public int getSize(){
	return(messages.size());
    }
}

class Consumer extends Thread{
    java.util.Random rn = new java.util.Random();
    MessageQueue queue;
    Consumer(MessageQueue queue){
	this.queue = queue;
    }
    public void run(){
	while (true){
	    try{
		Thread.sleep((int) (200*rn.nextDouble()));
	    }
	    catch(InterruptedException ie){}
	    String message = queue.get();
	    System.out.printf("Got Message[%d]:%s\n",
			      queue.getSize(),
			      message);
	}
    }
}

class Producer extends Thread{
    java.util.Random rn = new java.util.Random();
    MessageQueue queue;
    Producer(MessageQueue queue){
	this.queue = queue;
    }
    public void run(){
	while (true){
	    try{
		Thread.sleep((int) (200*rn.nextDouble()));
	    }
	    catch(InterruptedException ie){}
	    queue.put();
	}
    }
}
