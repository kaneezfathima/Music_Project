package processInformation;
import history.playlistBean;
import history.playlistDAO;
import history.songsTableDAO;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpSession;

import org.apache.catalina.connector.Request;

import registerInformation.RegisterBean;
import loginInformation.UserBean;

public class createFiles {
public static String userName;
playlistBean pb=new playlistBean();
	//process user information  first
	public void  userInformation(String user){

		System.out.println("user.............."+user);
		userName=user;		
		//SetUserInformation
		pb.setUser_name(userName);
	}
	
	//now get the listening history
	//  home/shahnaz/workspace/Music_Website/WebContent/audioFiles/playList.m3u
	public String addToSongsFile(String s) {
		Map<String,Integer> hmap=new HashMap<String, Integer>();
		FileWriter fw= null;
		File file =null;
		FileWriter fwP= null;
		File plylist =null;
		try {
			file=new File("/home/shahnaz/dataset_downloads/my_files/songs.txt");
			plylist= new File("/home/shahnaz/workspace/Music_Website/WebContent/audioFiles/playList.m3u");
			
			if(!file.exists())
			{
				file.createNewFile();
			}
			fw = new FileWriter(file,true);

			if(!plylist.exists())
			{
				plylist.createNewFile();
				System.out.println("PLY FILE..............");
			}
			fwP = new FileWriter(plylist,false);

			//go through the string s and store them in hash map
			for (String strs: s.split(",")){
				 int st=strs.indexOf('"');
			        String s2=strs.substring(st+1);

			        int en=s2.indexOf('"');
			        String s3=s2.substring(0,en);
					System.out.println(s3);

			       
				if (!hmap.containsKey(s3)) {
					hmap.put(s3, 1);
				} else {
					hmap.put(s3, hmap.get(s3)+1);
				}

			}
			//iterate through hashmap
			for (Map.Entry<String, Integer> entry : hmap.entrySet()) {
				String key = entry.getKey();
				Integer value = entry.getValue();
				fw.write(key+"\t"+value+'\n');   
				
				fwP.write("http://localhost:8085/Music_Website/audioFiles/"+key+".mp3"+"\n");
			}
			fw.flush();fwP.flush();
			fw.close();fwP.close();
			System.out.println("File Writed Succesfully");
		} catch (IOException e) {

			e.printStackTrace();
		}
		//update triplet.txt file too
		createFiles cf=new createFiles();
		songsTableDAO sd= new songsTableDAO();
		String str=sd.currentSongList(hmap);
		cf.addToTriplet(hmap);
		return str;
	}
	public void addToTriplet(Map<String,Integer> hmap) {

		FileWriter fw= null;
		File file =null;
		try {
			file=new File("/home/shahnaz/dataset_downloads/my_files/triplet.txt");
			if(!file.exists())
			{
				file.createNewFile();
			}
			fw = new FileWriter(file,true);
			
			//get username
			String user=userName;
			System.out.println("user.........................."+user);
			//try to insert into date all the values username,songid,count
			//iterate through hashmap
			
			playlistDAO pdo=new playlistDAO();
			for (Map.Entry<String, Integer> entry : hmap.entrySet()) {
				String key = entry.getKey();
				Integer value = entry.getValue();
				fw.write(user + "\t"+key+"\t"+value+'\n');   
				System.out.println(user + "\t"+key+"\t"+value+'\n');
				pb.setUser_name(user);
				pb.setSongId(key);
				pb.setCount(value);
				pdo.addOrUpdateRecords(pb);
			}
			fw.flush();
			fw.close();
			System.out.println("File Writed Succesfully");


			}
			
		 catch (IOException e) {

			e.printStackTrace();
		}


		return;
	}
}
