public class GetStateEx{
    
    public static void main(String[] args){
	Thread t1 = new Thread(
			       new Runnable(){
				   public void run(){
				       java.util.Scanner scan = new java.util.Scanner(System.in);
				       String input = scan.nextLine();
				   }
			       });
	
	Thread t2 = new Thread()(
			       new Runnable(){
				   public void run(){
				       while (true){
					   
				       }
				   }
			       });
	
	Thread t3 = new Thread(
			       new Runnable(){
				   public void run(){
				       System.out.println("thread 3 ...");
				   }
			       });
	
	
	System.out.println(t1.getState());
	System.out.println(t2.getState());
	System.out.println(t3.getState());
	
	t1.start();
	t2.start();
	t3.start();
	
	while (true){
	    System.out.println(t1.getState());
	    System.out.println(t2.getState());
	    System.out.println(t3.getState());
	    try{
		Thread.sleep(10000);
	    }
	    catch(InterruptedException ie){}
	}
	
    }
}