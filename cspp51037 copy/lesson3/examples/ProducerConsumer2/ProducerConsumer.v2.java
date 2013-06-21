import java.util.Vector; 
 
class Producer extends Thread { 
    static final int MAXQUEUE = 5; 
    private Vector<String> messages = new Vector<String>(); 
  
    public void run() { 
        try { 
            while ( true ) { 
                putMessage(); 
                sleep( 1000 ); 
            } 
        }  
        catch( InterruptedException e ) { } 
    } 
 
    private synchronized void putMessage() 
        throws InterruptedException { 
        
        while ( messages.size() == MAXQUEUE ) 
            wait(); 
        messages.addElement( new java.util.Date().toString() ); 
        notify(); 
    } 
 
    // Called by Consumer 
    public synchronized String getMessage() 
        throws InterruptedException { 
        notify(); 
        while ( messages.size() == 0 ) 
            wait(); 
        String message = (String)messages.firstElement(); 
        messages.removeElement( message ); 
        return message; 
    } 
} 
 
class Consumer extends Thread { 
    Producer producer; 
    String name; 
     
    Consumer(String name, Producer producer) { 
        this.producer = producer; 
        this.name = name; 
    } 
  
    public void run() { 
        try { 
            while ( true ) { 
                String message = producer.getMessage(); 
                System.out.println(name + " got message: " + message); 
                sleep( 2000 ); 
            } 
        }  
        catch( InterruptedException e ) { } 
    } 
  
    public static void main(String args[]) { 
        Producer producer = new Producer(); 
        producer.start(); 
	 
        // Start two this time 
        new Consumer( "One", producer ).start(); 
        new Consumer( "Two", producer ).start(); 
    } 
} 
