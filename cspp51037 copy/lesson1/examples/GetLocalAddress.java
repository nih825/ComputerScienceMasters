//get the local InetAddress
import java.net.*;
public class GetLocalAddress{
    public static void main(String[] args){
	try{
	    InetAddress address = InetAddress.getLocalHost();
	    System.out.println(address);
	}
	catch(UnknownHostException uhe){
	    System.out.println("Can't find computer's address!");
	}
    }
}
