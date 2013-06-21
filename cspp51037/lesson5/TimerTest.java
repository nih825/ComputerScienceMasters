import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ExTimer{
    public static void main(String[] args){
	EventQueue.invokeLater(new Runnable(){
		public void run(){
		    TimerTestFrame gui = new TimerTestFrame();
		    gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		    gui.setVisible(true);
		}
	    });
    }
}

class TimerTestFrame extends JFrame{

    JButton purchaseBut = new JButton("purchase");
    JButton listBut = new JButton("list");
    JTextField purchaseBox = new JTextField(10);
    JTextArea infoArea = new JTextArea();
    JPanel butPanel = new JPanel();
    JPanel textPanel = new JPanel();

    TimerTestFrame(){
	this.setSize(400,400);
	textPanel.setBackground(Color.WHITE);
	this.add(butPanel,BorderLayout.NORTH);
	this.add(textPanel,BorderLayout.CENTER);
	butPanel.add(purchaseBut);
	butPanel.add(listBut);
	butPanel.add(purchaseBox);
	textPanel.add(infoArea);

	purchaseBut.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent ae){
		    int confirm = 
			JOptionPane.showConfirmDialog(null,"Purchased 1 " + 
						      purchaseBox.getText());
		}
	    });

	Timer infoTask = new Timer(2000,new TaskTimer(this.infoArea));
	infoTask.start();
    }

}

class TaskTimer implements ActionListener{
    String itemList[] = {"shoes","jewelry","handbags","mens suits","swimwear"};
    JTextArea output;
    TaskTimer(JTextArea output){
	this.output = output;
    }

    public void actionPerformed(ActionEvent ae){
	java.util.Random rn = new java.util.Random();
	final int ranVal = rn.nextInt(itemList.length);
	//shouldn't have to run in the event dispatching thread.
	output.append("sale on " + itemList[ranVal] + 
				   " beginning now\n");

	//	EventQueue.invokeLater(new Runnable(){
	//		public void run(){
	//		    output.append("sale on " + itemList[ranVal] + 
	//				   " beginning now\n");
	//		}
	//	    });
    }

}