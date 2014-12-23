package history;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Vector;
import java.util.Collections;
import java.util.Set;


import loginInformation.ConnectionManager;

public class songsTableDAO {

	static Connection currentCon = null;
	static ResultSet rs = null;  

	public String currentSongList(Map<String,Integer> hmap)
	{
		String str="";
		Set<String> keySet= new HashSet<String>();

		//iterate through hashmap
		for (Map.Entry<String, Integer> entry : hmap.entrySet()) {
			String key = entry.getKey();
			// for each key get the set of song list
			songsTableDAO sd=new songsTableDAO();
			if( (str==null)||str.isEmpty())
			{
				keySet.add(key);
				str=sd.getRecords(key,keySet);
			}
			else
			{
				str=str+sd.getRecords(key,keySet);
			}
		}
		return str;
	}

	public String getRecords(String sid,Set<String> keySet ) {


		//preparing some objects for connection 
		Statement stmt = null; 

		String searchQuery ="SELECT list FROM songs_tb WHERE songId='"+ sid+"';";


		System.out.println("Query: "+searchQuery);

		try 
		{
			//connect to DB 
			currentCon = ConnectionManager.getConnection();
			stmt=currentCon.createStatement();
			rs = stmt.executeQuery(searchQuery);	

			//Vector<String> v=new Vector<String>();
			Set<String> s= new HashSet<String>();

			//if sid exists set the isValid variable to true
			while(rs.next()){
				String snglist = rs.getString(1);
				// String snglist1 = rs.getString("list");
				System.out.println(snglist);
				//System.out.println("---------------");
				// System.out.println(snglist1);
				for (String strs: snglist.split("\\|")){
					//	v.addElement(strs);
					if(!keySet.contains(strs))
					{
						s.add(strs);
					}
					System.out.println(strs);
				}	

			}
			//System.out.println("vector size:"+v.size());
			System.out.println("Set size:"+s.size());
			List<String> buddi = new ArrayList<String>(s);

			if(buddi.size() >0)
			{
				Collections.shuffle(buddi);
				int len=10;
				if(buddi.size()<10)
				{
					len=buddi.size();
				}
				//Print out top10 recommendations
				System.out.println("TOP \t"+len+":");
				String myString="";
				for (int i=0;i<len;i++)
				{
					if( (myString==null)||myString.isEmpty())
					{
						// myString = myString+(String) v.elementAt(i)+":";
						myString=buddi.get(i)+".jpg"+":";
					}
					else
					{
						myString = myString+buddi.get(i)+".jpg"+":";
					}
					System.out.println(buddi.get(i));
				}
				System.out.println(myString);
				return  myString;


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

			if (currentCon != null) {
				try {
					currentCon.close();
				} catch (Exception e) {
				}

				currentCon = null;
			}
		}

		return null;

	}	

}
