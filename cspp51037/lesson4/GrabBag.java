import java.util.Vector;
public class GrabBag{
    private Vector<Integer> bag;
    //create the initial bag stuffed with size
    //integer objects from [0,size-1]
    GrabBag(int size){
	bag = new Vector<Integer>(size);
	for (int i = 0; i < size; ++i)
	    bag.add(i);
    }
    //each thread will grab the next element
    //in the list and remove from the list
    //note that we will probably need to consider
    //synchronization here. we'll deal with that later
    public synchronized int grabNext(){
	int val = -1;
	if (!this.empty()){
	    val = bag.firstElement();
	    bag.removeElementAt(0);
	}
	return val;
    }

    //check if the bag is empty
    //might need to consider synch
    //here also
    public synchronized boolean empty(){
	if (bag.size() == 0)
	    return true;
	else
	    return false;
    }

    //main method to do grabbing 
    public static void main(String[] args){
	GrabBag bag = new GrabBag(Integer.parseInt(args[0]));
	Grabber g1 = new Grabber(bag);
	Grabber g2 = new Grabber(bag);
	g1.start();
	g2.start();
    }
}

class Grabber extends Thread{
    //this is the big communal bag
    private GrabBag bag;
    //this is my own small private bag of stuff grabbed
    private Vector<Integer> myStuff;
    //non-static class scope variables are allocated
    //independently for each instance of class, so this
    //should work fine for each thread.
    private int itemsGrabbed;
    //static variables only have one instance in memory and
    //thus each thread increments the same internal copy of
    //totalItemsGrabbed
    private static int totalItemsGrabbed = 0;
    Grabber(GrabBag bag){
	this.bag = bag;
	myStuff = new Vector<Integer>(1000);
	itemsGrabbed = 0;
    }

    public void run(){
	while (!bag.empty()){
	    int val = bag.grabNext();
	    if (val != -1){
		myStuff.add(val);
		++itemsGrabbed;
		++totalItemsGrabbed;
	    }
	}
	System.out.printf("I grabbed %d, total grabbed %d\n",
			  itemsGrabbed,totalItemsGrabbed);
    }
}