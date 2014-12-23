package registerInformation;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


import registerInformation.RegisterDAO;
import registerInformation.RegisterBean;
@WebServlet("/RegisterServlet")
public class RegisterServlet extends HttpServlet {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public RegisterServlet() {
        super();
        // TODO Auto-generated constructor stub
    }
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		try
		{	    

		     RegisterBean nwuser = new RegisterBean();
		     nwuser.setFirstName(request.getParameter("fName"));
		     nwuser.setLastName(request.getParameter("lName"));
		     nwuser.setUser_name(request.getParameter("un"));
		     nwuser.setPwd(request.getParameter("pw"));
		     nwuser.setEmail(request.getParameter("email"));
		     RegisterBean nwuser_ret = RegisterDAO.login(nwuser);
			   		    
		     if (nwuser_ret != null)
		     {
			        
		          HttpSession session = request.getSession(true);	    
		          session.setAttribute("currentSessionRegUser",nwuser); 
		          response.sendRedirect("Hello.jsp"); //logged-in page      		
		     }
			        
		     else 
		          response.sendRedirect("error.jsp"); //error page 
		} 
				
				
		catch (Throwable theException) 	    
		{
		     System.out.println(theException); 
		}
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

}
