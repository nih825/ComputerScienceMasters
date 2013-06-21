import java.util.List;
import java.util.ArrayList;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.awt.Color;

public class Ball{
    private int size;
    private double x,y;
    private double u,v;
    private Color color;
    private double diameter;
    private double dx=1;
    private double dy=1;
    private ArrayList<Ball> collisionList;

    public static int SMALL=0,MEDIUM=1,LARGE=2;

    Ball(int size, double xpos, double ypos,
	 double xvel, double yvel, Color color){
	this.size = size;
	this.x = xpos;
	this.y = ypos;
	this.u = xvel;
	this.v = yvel;
	this.color = color;

	if (size == SMALL)
	    diameter = 15.0;
	else if (size == MEDIUM)
	    diameter = 20.0;
	else if (size == LARGE)
	    diameter = 25.0;
	
	collisionList = new ArrayList<Ball>(3);
    }

    public ArrayList<Ball> getCollisionList(){
	return this.collisionList;
    }

    public void toggleDelta(){
	dx = -dx;
	dy = -dy;
    }

    public void updatePosition(Rectangle2D bounds,List<Ball> ballList){
	collisionList.clear();

	x += dx;
	y += dy;

	//check wall boundary
	if (x < bounds.getMinX())
	    { 
		x = bounds.getMinX();
		dx = -dx;
	    }
	if (x + diameter >= bounds.getMaxX())
	    {
		x = bounds.getMaxX() - diameter; 
		dx = -dx; 
	    }
	if (y < bounds.getMinY())
	    {
		y = bounds.getMinY(); 
		dy = -dy;
	    }
	if (y + diameter >= bounds.getMaxY())
	    {
		y = bounds.getMaxY() - diameter;
		dy = -dy; 
	    }

	//check collisions
	Ellipse2D c1 = getShape();
	for (Ball b:ballList){
	    if (this == b) continue;
	    Ellipse2D c2 = b.getShape();
	    if (c1.intersects(c2.getBounds2D())){
		collisionList.add(b);
	    }
	}
    }

    public Color getColor(){
	return(this.color);
    }
    
    public double getX(){
	return(this.x);
    }

    public double getY(){
	return(this.y);
    }

    public double getU(){
	return(this.u);
    }

    public double getV(){
	return(this.v);
    }

    public double getSize(){
	return(this.size);
    }

    public double getDiameter(){
	return(this.diameter);
    }

    public Ellipse2D getShape(){
	return new Ellipse2D.Double(x,y,diameter,diameter);
    }
}
