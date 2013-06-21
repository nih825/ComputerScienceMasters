import java.util.*;
import java.util.concurrent.*;
/*
  this is a modified version of the Join example of lesson3 using
  Callable and Future rather than join
*/
public class ExJoin{
    private java.util.Scanner in = new java.util.Scanner(System.in);
    private boolean read = false;
    ExecutorService pool = Executors.newFixedThreadPool(3);    
    Future<Integer> f = null;

    ExJoin(){
	while (true){
	    PROMPT();
	    
	    String input = in.nextLine();
	    if (input.equals("help"))
		showHelp();
	    else if (input.equals("getData")){
		f = pool.submit(new Callable<Integer>(){
			public Integer call(){
			    try{
				Thread.sleep(10000);
			    }
			    catch(InterruptedException ie){}
			    read = true;
			    return(new Integer(1));
			}
		    });
	    }
	    
	    else if (input.equals("getQuote")){
		if (f == null)
		    System.out.println("no data available");
		
		if (f != null){
		    Integer val = null;
		    if (read == false){
			javax.swing.JOptionPane.showMessageDialog(null,"Finishing reading data ...");
			try{
			    val = f.get();
			}
			catch(ExecutionException ee){}
			catch(InterruptedException ie){} 
		    }
		    System.out.println("quote is ..." + val);
		}
	    }
	    
	    else if (input.equals("exit")){
		System.exit(0);
	    }
	    else 
		System.out.println("Command not found");
	}
    }
    public static void showHelp(){
	System.out.println("help menu ...");
    }
    public static void PROMPT(){
	System.out.print(">> ");
    }
    
    public static void main(String[] args){
	new ExJoin();
    }
    
}

