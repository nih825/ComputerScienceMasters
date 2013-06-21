public class SpendersSavers{
    SpendersSavers(){


    }

    public static void main(String[] args){
	Account acc = new Account(100);
	Spender sp1 = new Spender(acc);
	Spender sp2 = new Spender(acc);
	Checker chk = new Checker(acc);
	Saver sv = new Saver(acc);
	Thread spender1Thread = new Thread(sp1);
	Thread spender2Thread = new Thread(sp2);
	Thread saverThread = new Thread(sv);
	Thread checkerThread = new Thread(chk);
	checkerThread.start();
	spender1Thread.start();
	spender2Thread.start();
	saverThread.start();


    }
}

class Checker implements Runnable{
    private Account account;

    Checker(Account acc){
	this.account = acc;
    }

    public void run(){
	while(true){
	    if (account.balance() < 0){
		System.out.println("Error: negative balance!!!!");
		System.exit(0);
	    }
	}

    }
}

class Saver implements Runnable{
    private Account account;

    Saver(Account acc){
	this.account = acc;
    }

    public void run(){
	while (true){
	    	    try{
	    		Thread.sleep(100);
	    	    }
	    	    catch(InterruptedException ie){}

	    account.deposit(8);
	    System.out.println("deposit made. New balance is: " + this.account.balance());
	}
    }
}

class Spender implements Runnable{
    private Account account;

    Spender(Account acc){
	this.account = acc;
    }

    public void run(){
	while (true){
	    	    try{
	    		Thread.sleep(75);
	    	    }
	    	    catch(InterruptedException ie){}

	    try{
		account.withdraw(10);
		System.out.println("withdrawal successful. New balance is: " + this.account.balance());
	    }
	    catch(InsufficientFundsException ife){
		System.out.println("Withdrawal NOT successful. No funds available!");
	    }
	}
    }
}

class Account{
    private double balance;

    Account(double initialBalance){
	this.balance = initialBalance;
    }
    
    public void deposit(double amount){
	balance += amount;
    }

    public void withdraw(double amount) throws InsufficientFundsException{
	if (this.balance >= amount)
	    balance -= amount;
	else
	    throw new InsufficientFundsException("remaining balance is: " + balance);
    }
    
    public double balance(){
	return this.balance;
    }
}

class InsufficientFundsException extends Throwable{
    InsufficientFundsException(String message){
	super(message);
    }
    
}