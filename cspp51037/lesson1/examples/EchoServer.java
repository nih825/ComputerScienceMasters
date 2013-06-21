import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.IOException;
import java.net.Socket;
import java.net.ServerSocket;
import java.util.Scanner;

public class EchoServer
{
    public static void main(String[] args)
    {
	final int port = 8189;
	try
	    {
		// establish server socket on (arbitrarily) port 8189
		ServerSocket s = new ServerSocket(port);
		System.out.println("Server up and waiting for connections on port " + port);
		
		// wait for client connection
		Socket incoming = s.accept();
		//once I get here it means someone connected
		try
		    {
			InputStream inStream = incoming.getInputStream();
			OutputStream outStream = incoming.getOutputStream();
			//wrap the streams for convenient higher-level i/o
			Scanner in = new Scanner(inStream);
			PrintWriter out = new PrintWriter(outStream, true /* autoFlush */);
			
			out.println("Hello! Enter BYE to exit.");
			
			// echo client input
			boolean done = false;
			while (!done)
			    {
				String line = in.nextLine();
				out.println("Echo: " + line);
				if (line.trim().equals("BYE")) done = true;
			    }
		    }
		finally
		    {
			incoming.close();
		    }
	    }
	catch (IOException e)
	    {
		e.printStackTrace();
	    }
    }
}
