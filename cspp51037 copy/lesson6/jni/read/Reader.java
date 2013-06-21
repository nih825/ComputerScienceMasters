import java.io.*;

class Reader{
    public native void read(byte[] arr, String file);
    static{
	System.loadLibrary("read");
    }

    public void writeToRead(String filename, int size){
	File file = new File(filename);
	DataOutputStream out = null;
	try{
	    out = new DataOutputStream(new FileOutputStream(file));

	    for (int i = 0;i < size; ++i)
		out.writeByte(i);
	    out.flush();
	    out.close();
	}
	catch(Exception e){
	    System.out.println(e);
	}
    }

    public static void main(String[] args){
	String file = "./data";
	int size = 100;
	Reader reader = new Reader();
	reader.writeToRead(file,size);
	byte[] f = new byte[size];
	reader.read(f,file);
	for (byte b:f) System.out.println(b);
    }
}
