import java.net.*;
import java.io.*;

public class DaytimeClient{
    public static void main(String[] args){
	String hostname;
	if (args.length > 0){
	    hostname = args[0];
	}
	else {
	    hostname = "nod.cs.uchicago.edu";
	}
	
	try{
	    Socket s = new Socket(hostname,13);
	    InputStream in = s.getInputStream();
	    StringBuffer time = new StringBuffer();
	    int c;
	    while ( (c = in.read() ) != -1) time.append( (char) c);
	    String timeString = time.toString().trim();
	    System.out.println("It is " + timeString + " at " + hostname);
	}

	catch (UnknownHostException e){
	    System.err.println(e);
	}

	catch (IOException e){
	    System.err.println(e);
	}
    }
    
}
