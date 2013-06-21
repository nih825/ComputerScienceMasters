import java.util.concurrent.locks.*;

class Store{
    private int nthings;
    private int nthings_init;
    Store(int n){
	this.nthings = n;
	this.nthings_init = n;
    }
    public synchronized int getThing() throws Exception{
	if (this.nthings > 0){
	    return --nthings;
	}
	else
	    throw new Exception();
    }

    public synchronized int things(){
	return(nthings);
    }
}

//can it happen that things returns > 0 but getThing then fails?
public class StoreThreadTest{
    private Client[] clients;
    private int nClients;
    private Store aStore = null;

    StoreThreadTest(Store s, int n){
	this.aStore = s;
	this.nClients = n;

	clients = new Client[nClients];
	for (int i=0;i<nClients;++i){
	    clients[i] = new Client(s,i);
	}
	for (int i=0;i<nClients;++i){
	    clients[i].start();
	}
    }

    public static void main(String[] args){
	Store aStore = new Store(10);
	new StoreThreadTest(aStore,10000);
    }
}

class Client extends Thread{
    private Store aStore;
    private int id;
    private Lock lock = new ReentrantLock();

    Client(Store s, int id){
	this.id=id;
	this.aStore = s;
    }

    public void run(){
	int n;

	while (true){
	    if (this.id < 50) yield();
	    synchronized(aStore){
	    if (aStore.things() > 0){
		System.out.println("Thread " + id + " made purchase");
		try{
		    n = aStore.getThing();
		}
		catch(Exception e){
		    System.out.println("something went wrong -- store out of things ...");
		}
	    }
	    else
		break;
	    }
	}
    }

    private int doIt(){
	int res=1;
	for (int i=0;i<1000;++i)
	    res+=i;
	return res;
    }
}
