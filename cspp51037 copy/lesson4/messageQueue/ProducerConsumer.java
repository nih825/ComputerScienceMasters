import java.util.Vector;
class ProducerConsumer{
    public static void main(String[] args){
	MessageQueue queue = new MessageQueue(100);
	Producer p = new Producer(queue);
	Consumer c = new Consumer(queue);
	p.start();
	c.start();

    }




}