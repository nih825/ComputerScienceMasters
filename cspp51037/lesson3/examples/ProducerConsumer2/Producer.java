import java.util.Vector; 
 
class Producer extends Thread { 
    MessageQueue queue;

    Producer(MessageQueue queue){
	this.queue = queue;
    }

    public void run() { 
        try { 
            while ( true ) { 
                queue.put(); 
                sleep( 500 ); 
            } 
        }  
        catch( InterruptedException e ) { } 
    } 
 
 
} 
 
  
 
