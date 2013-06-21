class Consumer extends Thread { 
    MessageQueue queue;
     
    Consumer(MessageQueue queue){
        this.queue = queue;
    } 
  
    public void run() { 
        try { 
            while ( true ) { 
                String message = queue.get(); 
                System.out.printf("Got Message[%d]:%s\n", queue.getSize(), message);
                sleep( 700 ); 
            } 
        }  
        catch( InterruptedException e ) { } 
    } 
}