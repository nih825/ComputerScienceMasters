import java.net.*;
import java.io.*;
import java.util.Scanner;

public class EchoClient{
    public static void main(String[] args){
	String hostname = "localhost";
	
	if (args.length > 0){
	    hostname = args[0];
	}

	PrintWriter networkOut = null;
	Scanner networkIn = null;
	Scanner userIn    = null;

	try{
	    //create a socket connection to port 8189 on host hostname
	    Socket s = new Socket(hostname, 8189);
	    //read input and output streams and wrap
	    networkIn = new Scanner(s.getInputStream());
	    networkOut = new PrintWriter(s.getOutputStream(),true);
	    userIn = new Scanner(System.in);
	    
	    System.out.println(networkIn.nextLine());
	    
	    while (true){
		System.out.print("Enter message: ");
		String theLine = userIn.nextLine();//block for key input
		networkOut.println(theLine);//send key input to server
		String reply = networkIn.nextLine(); // read server response
		System.out.println("Server responded: " + reply); //print reply to screen
		if (reply.equals("Echo: BYE")){
		    System.out.println("connection closed");
		    System.exit(0);
		}
	    }
	}
	catch( IOException e){
	    System.err.println(e);
	}
	
	finally {
	    try{
		if (networkIn != null) networkIn.close();
		if (networkOut != null) networkOut.close();
	    }
	    catch(Exception e){}
	}
    }
}
