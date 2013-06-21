import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class ThreeParams extends HttpServlet{
    public void doPost(HttpServletRequest req,
		       HttpServletResponse res)
	throws IOException, ServletException{
	//these parameters are part of post payload
	//they can be bundled from html page form or
	//directly from client (e.g. java) program
	String p1 = req.getParameter("last");
	String p2 = req.getParameter("first");
	String p3 = req.getParameter("social");
	StringBuffer newSocial = new StringBuffer();
	newSocial.append(p3 + "-123");
	
	PrintWriter out = res.getWriter();
	out.println("new extended social for " + p2 + "," + p1 + "is " + 
		    newSocial);
	out.flush();
	out.close();
    }
}