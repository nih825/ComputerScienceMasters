import java.net.*;
import java.io.*;
public class NSLookup{
    public static void main(String[] args){
	if (args.length > 0) { //use command line
	    for (int i = 0; i < args.length; ++i){
		System.out.println(lookup(args[i]));
	    }
	}
	else{
	    BufferedReader bin = new BufferedReader(
			    new InputStreamReader(System.in));
	    System.out.println
		("Enter names and IP addresses. Enter \"exit\" to quit.");
	    try{
		while (true) {
		    String host = bin.readLine();
		    if (host.equals("exit")) break;
		    System.out.println(lookup(host));
		}
	    }
	    catch(IOException e){
		System.err.println(e);
	    }
			    		
	}
    }

    private static String lookup(String host){
	InetAddress thisComputer;
	byte[] address;
	
	try{
	    thisComputer = InetAddress.getByName(host);
	    address = thisComputer.getAddress();
	}
	catch (UnknownHostException e){
	    return("cannot find host " +  host);
	}

	if (isHostName(host)){
	    //print the IP address
	    String dottedQuad = "";
	    for (int i = 0; i < address.length; i++){
		int unsignedByte = address[i] < 0 ? address[i] + 256 : address[i];
		dottedQuad += unsignedByte;
		if (i != address.length - 1) dottedQuad += ".";
	    }
	    return(dottedQuad);
	}

	else{
	    return(thisComputer.getHostName());
	}

    }

    private static boolean isHostName(String host){
	//look for char that is not a digit or a .
	char[] ca = host.toCharArray();
	for (int i = 0; i < ca.length; ++i){
	    if (!Character.isDigit(ca[i])){
		if (ca[i] != '.') return (true);
	    }
	}
	return(false);
    }
}
