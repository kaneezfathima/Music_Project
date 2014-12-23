package registerInformation;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;

import java.sql.PreparedStatement;


import loginInformation.ConnectionManager;
import registerInformation.RegisterBean;

public class RegisterDAO {
	static Connection currentCon = null;
	  		
	   public static RegisterBean login(RegisterBean bean) {
		
	      //preparing some objects for connection 
	     
	      PreparedStatement pstmt=null;
	      String usrName = bean.getUser_name();
	      String fName = bean.getFirstName();
	      String lName = bean.getLastName();
	      String mail = bean.getEmail();
	      String pwd= bean.getPwd();
		    
	  
	   System.out.println("Your user name is " + usrName);          
	   System.out.println("Your password is " + pwd);
	   System.out.println("Your first name is " + fName);
	   System.out.println("Your last Name is " + lName);
	   System.out.println("Your mail is " + mail);
		    
	   try 
	   {
	      //connect to DB 
	      currentCon = ConnectionManager.getConnection();
	      //to insert rows we need to use preparedstatement
	      	pstmt=currentCon.prepareStatement("Insert into login_tb(user_name,pwd,firstName,lastName,email) VALUES(?,?,?,?,?)");
	         pstmt.setString(1,usrName );
	         pstmt.setString(2,pwd);
	         pstmt.setString(3,fName);
	         pstmt.setString(4,lName);
	         pstmt.setString(5,mail);
	         int count=pstmt.executeUpdate();
	         System.out.println("No of rows inserted: "+count);
	 
	   } 

	   catch (Exception ex) 
	   {
	      System.out.println("Log In failed! " + ex);
	   } 
	   finally 
	   {
	      if (pstmt != null) {
	         try {
	            pstmt.close();
	         } catch (Exception e) {}
	            pstmt = null;
	         }
		
	      if (currentCon != null) {
	         try {
	            currentCon.close();
	         } catch (Exception e) {
	         }

	         currentCon = null;
	      }
	   }

	return bean;
		
	   }
}
