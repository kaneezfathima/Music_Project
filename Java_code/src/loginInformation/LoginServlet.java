package loginInformation;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import processInformation.createFiles;

/**
 * Servlet implementation class LoginServlet
 */
@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public LoginServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		try
		{	    

		     UserBean user = new UserBean();
		     user.setUser_name(request.getParameter("un"));
		     user.setPwd(request.getParameter("pw"));

		     UserBean user_ret = UserDAO.login(user);
			   
		     if(user_ret ==null){ response.sendRedirect("registerPage.jsp"); //go to register page
		     
		     }
		     else if (user_ret != null)
		     {
			        
		          HttpSession session = request.getSession(true);	    
		          session.setAttribute("currentSessionUser",user); 
		          
		          createFiles cf=new createFiles();
		          cf.userInformation(user.getUser_name());
		         /* userReco ur= new userReco();
		          ur.loginInfo(user.getUser_name());*/
		          response.sendRedirect("userLogged.jsp"); //log in page   
		          
		     }   
		} 
				
				
		catch (Throwable theException) 	    
		{
		     System.out.println(theException); 
		}
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

}
