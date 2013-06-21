class HelloWorld{
    /* any class can have zero or more native methods
       and zero or more regular ones */
    public native void displayHelloWorld();

    public void foo(){
	System.out.println("fooing");
    }

    /* this is required so java can find libhello.so, where
       presumably the native method(s) are defined */
    static{
	System.loadLibrary("hello");
    }
    
    public static void main(String[] args){
	HelloWorld h = new HelloWorld();
	h.displayHelloWorld();
    }


}
