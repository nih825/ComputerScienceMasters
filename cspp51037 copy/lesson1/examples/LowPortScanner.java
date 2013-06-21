import java.net.*;
import java.io.*;
//low port scanner version one
class LowPortScanner{
    public static void main(String[] args){
	String host = "localhost"; 
	
	if (args.length > 0) {
	    host = args[0];
	}

	for (int i = 1; i < 10000; i++){
	    try{
		Socket s = new Socket(host,i);
		System.out.println("there is a server on port " +
				   i + " of " + host);
	    }
	    catch(UnknownHostException uhe){
		System.err.println(uhe);
		break;
	    }
	    
	    catch(IOException ioe){
		//must not be a server
	    }
	}//end for
    }//end main
}//end LowPortScanner
