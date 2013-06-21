import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ExPaint{
    public static void main(String[] args){
	EventQueue.invokeLater(new Runnable(){
		public void run(){
		    MyFrame gui = new MyFrame();
		    gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		    gui.setVisible(true);
		}
	    });
    }
}

class MyFrame extends JFrame{
    private JButton startBut = new JButton("start");
    private JButton stopBut  = new JButton("start");
    private JButton pauseBut = new JButton("pause");

    MyFrame(){
	setTitle("Test");
	setSize(400,400);
	JPanel butPanel = new JPanel();
	ImagePanel imgPanel = new ImagePanel();
	FlowLayout layout = new FlowLayout(FlowLayout.CENTER);
	butPanel.setLayout(layout);
	this.add(butPanel,BorderLayout.NORTH);
	this.add(imgPanel,BorderLayout.CENTER);
	butPanel.add(startBut);
	butPanel.add(pauseBut);
	butPanel.add(stopBut);
    }

}

class ImagePanel extends JPanel{
    ImagePanel(){

    }

    public void paintComponent(Graphics g){
	//	g.drawString("hello world", 20,20);
	Image img = null;
	try{
	    img = javax.imageio.ImageIO.read(new java.io.File("photo2.jpg"));
	}
	catch(Exception e){e.printStackTrace();}
	g.drawImage(img,0,0,null);
    }
    
}