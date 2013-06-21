import java.util.StringTokenizer;
public class ExJoin{
    private java.util.Scanner in = new java.util.Scanner(System.in);
    private boolean read = false;
    private Thread dataReadingThread = null;
    private enum Symbol{ABG,ABT,ABVT,BAC,FAM,FAV,FPB,KAI};
    private Symbol thisStock;
    ExJoin(){
	while (true){
	    PROMPT();
	    
	    String input = in.nextLine();
	    StringTokenizer st = new StringTokenizer(input);
	    String cmd = st.nextToken();
	    if (cmd.equals("help"))
		showHelp();
	    else if (cmd.equals("setStock")){
		String arg = st.nextToken();
		try{
		    this.thisStock = Symbol.valueOf(arg);
		    System.out.println("setting stock to " + thisStock);
		}
		catch(IllegalArgumentException e){
		    System.out.println("invalid symbol");
		}
	    }
	    else if (cmd.equals("getData")){
		//pretend that it takes 10 seconds to read the data
		dataReadingThread = new Thread(
			       new Runnable() {
				   public void run() {
				       try{
					   Thread.sleep(10000);
				       }
				       catch(InterruptedException ie){}

				       //set flag once reading is done
				       //so it is known for future getQuote
				       //calls
				       read = true;
				   }
			       });
		dataReadingThread.start();
	    }
	    
	    else if (cmd.equals("getQuote")){
		if (dataReadingThread == null)
		    System.out.println("no data available");
		
		if (dataReadingThread != null){
		    if (read == false){
			System.out.println("busy reading data, please wait ...");
			try{
			    //blocks current thread until dataReadingThread
			    //is complete, thus ensuring that our code
			    //is properly synchronized
			    dataReadingThread.join();
			}
			catch(InterruptedException ie){}
		    }
		    System.out.println("quote is ...");
		}
	    }
	    
	    else if (cmd.equals("exit")){
		System.exit(0);
	    }
	    else if (cmd.equals("list")){
		listSymbols();
	    }
	    else 
		System.out.println("Command not found");
	}
    }
    public void showHelp(){
	System.out.println("help menu ...");
    }
    public void PROMPT(){
	System.out.print(">> ");
    }
    
    public void listSymbols(){
	for (Symbol s: Symbol.values())
	    System.out.println(s);
    }
    public static void main(String[] args){
	new ExJoin();
    }
    
}

