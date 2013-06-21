public class WallTicker{
    public static void main(String[] args){
	Wall wall = new Wall();
	Writer writer = new Writer(wall);
	Reader reader = new Reader(wall);
	TimeOut to = new TimeOut(20);
	to.start();
	writer.start();
	reader.start();
    }
}

class Wall{
    private String val;
    private String[] sayings = {"what goes around comes around",
				"the sky is falling",
				"you get you pay for"};
    java.util.Random rn = new java.util.Random();
    String lastVal;
    boolean changed;
    //write and read need to be modified such that it is guaranteed
    //that the Reader doesn't miss any change in value from the Writer.
    //Put simply, if the writer changes its saying on the wall, it must
    //force that the reader read it.
    public synchronized String read(){
	String d = this.val;
	if (changed){
	    changed = false;
	    notify();
	}
	return(d);
    }

    public synchronized void write(){
	this.val = sayings[rn.nextInt(sayings.length)];
	if (!val.equals(lastVal)){
	    changed = true;
	    try{
		wait();
	    }
	    catch(InterruptedException ie){}
	}
	this.lastVal = val;
    }
}

//this class just continuously writes one of our
//three sayings randomly on the Wall
class Writer extends Thread{
    Wall wall;
    Writer(Wall wall){
	this.wall = wall;
    }
    public void run(){
	while (true){
	    try{
		Thread.sleep(10);
	    }
	    catch(InterruptedException ie){}
	    wall.write();
	}
    }

}
//this class just continuously
//reads what is on Wall and prints it.
// note that we will add rule 1 soon
class Reader extends Thread{
    Wall wall;

    Reader(Wall wall){
	this.wall = wall;
    }

    public void run(){
	while (true){
	    try{
		Thread.sleep(500);
	    }
	    catch(InterruptedException ie){}
	    String saying = wall.read();
	    System.out.println(saying);
	}
    }


}

class TimeOut extends Thread{
    int time;
    TimeOut(int time){
	this.time = time;
    }
    public void run(){
	try{
	    Thread.sleep(time*1000);
	}
	catch(InterruptedException io){}
	System.out.println("time limit up, shutting down ..");
	System.exit(1);
    }

}