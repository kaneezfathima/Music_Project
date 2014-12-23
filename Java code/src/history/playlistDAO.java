package history;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;

import loginInformation.ConnectionManager;
import loginInformation.UserBean;

public class playlistDAO {

	   static Connection currentCon = null;
	   static ResultSet rs = null;  
		
		
		
	   public void addOrUpdateRecords(playlistBean bean) {
		
	      //preparing some objects for connection 
	      Statement stmt = null; 
	      PreparedStatement pstmt=null;

	      String username = bean.getUser_name();    
	      String songid = bean.getSongId();  
	      int count=bean.getCount();
		    
	      String searchQuery =
	            "select * from triplet_tb where user_name='"+ username+ "' AND songId='"+ songid+ "';";
		    
	   // "System.out.println" prints in the console; Normally used to trace the process
	   System.out.println("Your user name is " + username);          
	   System.out.println("Your songid is " + songid);
	   System.out.println("Your count is:"+count);
	   System.out.println("Query: "+searchQuery);
		    
	   try 
	   {
	      //connect to DB 
	      currentCon = ConnectionManager.getConnection();
	      stmt=currentCon.createStatement();
	      rs = stmt.executeQuery(searchQuery);	        
	      boolean more = rs.next();
		       
	      // if user and song match does not exist set the isValid variable to false
	      if (!more) 
	      {
	         System.out.println("Record not found, so insert new record");
	         
	         pstmt=currentCon.prepareStatement("Insert into triplet_tb(user_name,songId,count) VALUES(?,?,?)");
	         pstmt.setString(1,username );
	         pstmt.setString(2,songid);
	         pstmt.setInt(3,count);
	        
	        
	         int countRows=pstmt.executeUpdate();
	         System.out.println("No of rows inserted: "+countRows);
	 
	      } 
		        
	      //if user exists set the isValid variable to true
	      else if (more) 
	      {
	          int myCount = rs.getInt("count");
	          myCount+=count;
	    	  pstmt=currentCon.prepareStatement("UPDATE triplet_tb SET count=? Where user_name= ? and songId=?");
	    	  pstmt.setInt(1, myCount);
	    	  pstmt.setString(2,username );
		      pstmt.setString(3,songid);
		      int countRows=pstmt.executeUpdate();
		         System.out.println("No of rows updated: "+countRows);
	      }
	   } 

	   catch (Exception ex) 
	   {
	      System.out.println("Playlist failed: An Exception has occurred! " + ex);
	   } 
		    
	   //some exception handling
	   finally 
	   {
	      if (rs != null)	{
	         try {
	            rs.close();
	         } catch (Exception e) {}
	            rs = null;
	         }
		
	      if (stmt != null) {
	         try {
	            stmt.close();
	         } catch (Exception e) {}
	            stmt = null;
	         }
		
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

	return;
		
	   }	

}
