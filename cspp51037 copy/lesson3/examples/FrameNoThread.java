import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

class FrameNoThread extends JFrame implements ActionListener{
    static int val = 0;
    JButton but1, but2 = null;
    JTextField text = null;
    FrameNoThread(){
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
	//generic time consuming operation
	if (ae.getSource() == but1){
	    while (true)
		System.out.println(++val);
	}
	// just define starting point of consuming operation
	// to have another button
	else if (ae.getSource() == but2){
	    this.val = Integer.parseInt(text.getText());
	}
    }
	
    public static void main(String[] args){
	FrameNoThread gui = new FrameNoThread();
	gui.setSize(400,400);
	gui.show();
    }
    
}
