import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class HW2Prototype{
    
    public static void main(String[] args){

	double xFrameSize = 1000;
	double yFrameSize = 1000;
	int nBalls=50;
	int[] sizeArray  = {Ball.SMALL, Ball.MEDIUM, Ball.LARGE};
	Color[] colorArray = {Color.RED, Color.BLUE};
	final ArrayList<Ball> ballList = new ArrayList<Ball>(2*nBalls);

	//initialize ball list
	Random rn = new Random();
	for (int i=0;i<nBalls;++i){
	    int ranSize = sizeArray[rn.nextInt(3)];
	    double ranX = rn.nextDouble()*xFrameSize;
	    double ranY = rn.nextDouble()*yFrameSize;
	    double ranU = rn.nextDouble();
	    double ranV = rn.nextDouble()*xFrameSize;
	    Color ranColor = colorArray[rn.nextInt(2)];
	    Ball b = new Ball(ranSize,ranX,ranY,ranU,ranV,ranColor);
	    ballList.add(b);
	}

	//"safe" way to start gui
	EventQueue.invokeLater(new Runnable(){
		public void run(){
		    MyFrame gui = new MyFrame(ballList);
		    gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		    gui.setVisible(true);
		}
	    });
    }
}

class MyFrame extends JFrame implements ActionListener{
    private JButton startBut = new JButton("start");
    private JButton stopBut  = new JButton("start");
    private JButton pauseBut = new JButton("pause");
    private JPanel ballPanel;
    private JPanel butPanel;
    private final ArrayList<Ball> ballList;

    MyFrame(final ArrayList<Ball> ballList){
	this.ballList = ballList;

	setTitle("Test");
	setSize(1000,1000);
	butPanel = new JPanel();
	ballPanel = new BallPanel(ballList);
	FlowLayout layout = new FlowLayout(FlowLayout.CENTER);
	butPanel.setLayout(layout);
	this.add(butPanel,BorderLayout.NORTH);
	this.add(ballPanel,BorderLayout.CENTER);
	butPanel.add(startBut);
	butPanel.add(pauseBut);
	butPanel.add(stopBut);
	startBut.addActionListener(this);
    }

    public void actionPerformed(ActionEvent ae){
	Animation anim = new Animation(ballPanel,ballList);
	Thread t = new Thread(anim);
	t.start();
    }
}


class Animation implements Runnable{
    JPanel ballPanel;
    List<Ball> ballList;

    Animation(JPanel panel,List<Ball> ballList){
	this.ballPanel = panel;
	this.ballList = ballList;
    }

    public void run(){
	for (int iter = 0; iter < 10000; ++iter){
	    int nBalls = ballList.size();
	    BallThread bt1 = 
		new BallThread(ballList.subList(0,(nBalls-1)/2),ballPanel);
	    BallThread bt2 = 
		new BallThread(ballList.subList(nBalls/2,nBalls-1),ballPanel);
	    bt1.start();
	    bt2.start();
	    try{
		bt1.join();
		bt2.join();
	    }
	    catch(InterruptedException ie){}
	    ballPanel.repaint();
	    try{
		Thread.sleep(2);
	    }
	    catch (InterruptedException ie){}
	}
    }
}


class BallThread extends Thread{
    private List<Ball> ballList;
    private JPanel ballPanel;

    BallThread(List<Ball> ballList,JPanel ballPanel){
	this.ballList = ballList;
	this.ballPanel = ballPanel;
    }

    public void run(){
	for (Ball b:ballList){
	    b.updatePosition(ballPanel.getBounds(),ballList);
	}
    }

}

class BallPanel extends JPanel{
    private List<Ball> ballList;
    private static int count = 0;

    BallPanel(List<Ball> ballList){
	this.ballList = ballList;
    }

    public void paintComponent(Graphics g){
	super.paintComponent(g);
	Graphics2D g2d = (Graphics2D)g;
	++count;
	for (Ball b:ballList){
	    g2d.setColor(b.getColor());
	    if (b.getCollisionList().isEmpty())
		g2d.fill(b.getShape());
	    else{
		b.toggleDelta();
		g2d.fill(b.getShape());
	    }
		
	}
	
    }
    
}

