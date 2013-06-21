import javax.swing.*;        
import java.awt.*;
import java.awt.event.*;

public class InterruptedEx implements ActionListener,Runnable{
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private JLabel result = new JLabel("answer");
    private JButton start = new JButton("start");
    private JButton stop = new JButton("stop");
    private Thread workerThread = new Thread(this);

    private void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("HelloWorldSwing");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Add the ubiquitous "Hello World" label.

        JLabel label = new JLabel("result");
	Container cp = frame.getContentPane();
	cp.setLayout(new FlowLayout());
	cp.add(result);
	cp.add(start);
	cp.add(stop);
	start.addActionListener(this);
	stop.addActionListener(this);
        //Display the window.
	frame.setSize(400,400);
        frame.setVisible(true);
    }

    public void actionPerformed(ActionEvent ae){

	if (ae.getSource() == start){
	    workerThread.start();
	}
	else if (ae.getSource() == stop){
	    workerThread.interrupt();
	    
	}
    }
    

    p!ublic void run(){
	boolean interrupted;
	long res=0;
	try{
	    Thread.sleep(10000);
	}
	catch(InterruptedException ie){
	    System.out.println(ie);
	    result.setText("I was interrupted");
	    return;
	}
    }    
    
    public static void main(String[] args) {
        //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
		public void run() {
		    new InterruptedEx().createAndShowGUI();
		}
	    });
    }
}

	//do something fake that is very time consuming in
	//event handler
	//	for (long i = 0;i<1000000L;++i){
	//	    for (long j=0;j<100000000L;++j){
	//		res = i*j-4;
	//	    }
	//	    result.setText(Long.toString(res));	    
	//	    interrupted = Thread.currentThread().isInterrupted();

	//	    if (interrupted) 
	//		return;
	}

