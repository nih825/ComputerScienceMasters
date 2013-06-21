public class Producer extends Thread {
    private CubbyHole cubbyhole;
    private int number;

    public Producer(CubbyHole c, int number) {
        cubbyhole = c;
        this.number = number;
    }

    public void run() {
        for (int i = 0; i < 10; i++) {
	    try{
		Thread.sleep((int) (Math.random() * 100));
	    }
	    catch(InterruptedException ie){};
            cubbyhole.put(i);
            System.out.println("Producer" + " put: " + i);
	    System.out.flush();
        }
    }
}
