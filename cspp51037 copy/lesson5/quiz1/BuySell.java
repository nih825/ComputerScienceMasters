public class BuySell{
    public static void main(String[] args){
	int nb = Integer.parseInt(args[0]);
	int ns = Integer.parseInt(args[1]);
	int ne = Integer.parseInt(args[2]);
	Buyer[] buyers = new Buyer[nb];
	Seller[] sellers = new Seller[ns];
	Exchange exchange = new Exchange(ne);
	for (int i = 0; i < nb; ++i)
	    buyers[i] = new Buyer(exchange);
	for (int i = 0; i < ns; ++i)
	    sellers[i] = new Seller(exchange);

	for (Buyer b:buyers)
	    b.start();
	for (Seller s:sellers)
	    s.start();
	    
    }
}

class Exchange{
    private int size;

    Exchange(int size){
	this.size = size;
    }

    public int buy(int nItems) {
	size -= nItems;
	return(size);
    }

    public int sell(int nItems){
	size += nItems;
	return(size);
    }

    public int getSize(){
	return(size);
    }
}

class Buyer extends Thread{
    Exchange exchange;
    java.util.Random rn;
    Buyer (Exchange ex){
	this.exchange = ex;
	rn = new java.util.Random();
    }

    public void run(){
	int itemsRemaining;
	while (true){
	    try{
		Thread.sleep(100);
	    }
	    catch(InterruptedException ie){}
	    int n = rn.nextInt(5);
	    itemsRemaining = exchange.buy(n);
	    System.out.println("Bought " + n + " items." +
			       "there are " + itemsRemaining + 
			       " items remaining");
	}
    }

}

class Seller extends Thread{
    Exchange exchange;
    java.util.Random rn;
    Seller (Exchange ex){
	this.exchange = ex;
	rn = new java.util.Random();
    }

    public void run(){
	while (true){
	    try{
		Thread.sleep(100);
	    }
	    catch(InterruptedException ie){}
	    int n = rn.nextInt(5);
	    int itemsRemaining = exchange.sell(n);
	    System.out.println("Sold " + n + " items." +
			       "there are " + itemsRemaining + 
			       " items remaining");
	}
    }

}
