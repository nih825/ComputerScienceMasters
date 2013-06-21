import java.util.Vector;
public class MessageQueue{
    private  int MAXQUEUE;
    private Vector<String> messages;
    
    MessageQueue(int size){
	MAXQUEUE = size;
	messages = new Vector<String>(); 
    }

    public int getSize(){
	return messages.size();
    }
    // Called by Producer
    public synchronized void put()
        throws InterruptedException { 

        while ( messages.size() == MAXQUEUE ){
	    System.out.println("queue full, waiting to drain ...");
            wait(); 
	}
        messages.addElement( new java.util.Date().toString() ); 
        notify(); 
    } 
    
    // Called by Consumer 
    public synchronized String get()
        throws InterruptedException { 
	//	notify(); 
        while ( messages.size() == 0 ){
	    System.out.println("queue empty, waiting to fill ...");
            wait(); 
	}
        String message = messages.firstElement(); 
        messages.removeElement( message ); 
        return message; 
    } 
    

}