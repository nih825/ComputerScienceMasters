import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

class FrameThread extends JFrame implements ActionListener, Runnable{
    static int val = 0;
    JButton but1, but2 = null;
    JTextField text = null;
    FrameThread(){
	Container cp = getContentPane();
	cp.setLayout(new FlowLayout(FlowLayout.CENTER));
	but1 = new JButton("go");
	but2 = new JButton("enter");

	text = new JTextField(10);
	cp.add(but1);
	cp.add(but2);
	cp.add(text);
	but1.addActionListener(this);
	but2.addActionListener(this);
    }

    public void actionPerformed(ActionEvent ae){
	if (ae.getSource() == but1){
	    Thread t = new Thread(this);
	    t.start();
	}
	else if (ae.getSource() == but2){
	    this.val = Integer.parseInt(text.getText());
	}
    }
	
    public void run(){

	while (true){
	    try{
		System.out.println(++val);
		Thread.sleep(10);
	    }
	    catch(Exception e){}
	}
    }

	
    public static void main(String[] args){
	FrameThread gui = new FrameThread();
	gui.setSize(400,400);
	gui.show();
    }
    
}
