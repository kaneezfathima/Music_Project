package history;
import java.util.Arrays;
import java.util.Iterator;

import org.json.simple.JSONArray;
import org.json.simple.JSONValue;
import org.json.simple.JSONObject;

import processInformation.createFiles;

import java.util.Enumeration;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import loginInformation.UserBean;
import loginInformation.UserDAO;
@WebServlet("/addToHistoryServlet")
public class addToHistoryServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public addToHistoryServlet() {
        super();
        // TODO Auto-generated constructor stub
    }
	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	response.setContentType("text/json");
    PrintWriter out = response.getWriter();

    try {
        String action = request.getParameter("action");
        String json = request.getParameter("json");
        JSONObject jsonData = (JSONObject) JSONValue.parse(json);
        
        String s1=((String)jsonData.get("lists")); 
        
        System.out.println("your string: "+s1);
        int st=s1.indexOf('[');
        int en=s1.indexOf(']');
        
        String s2=s1.substring(st+1, en);
         
        String status = "SUCESS";
      

     /*   JSONObject result = new JSONObject();
        result.put("message",status);
        String jsonResult = JSONObject.toJSONString(result);
        out.println(jsonResult);
       createFiles cf= new createFiles();
        cf.addToSongsFile(s2); */
        createFiles cf= new createFiles();

        String temp=cf.addToSongsFile(s2);
        JSONObject result = new JSONObject();
        //result.put("message",status);
        result.put("message",temp);
        String jsonResult = JSONObject.toJSONString(result);
        out.println(jsonResult);
        
       
    }
    catch (Exception ex) {
        out.println("{\"message\":\"Error - caught exception in ExportServlet\"}");
    } finally {
        out.flush();
        out.close();
    }
}

protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    doGet(request, response);
}	
}
