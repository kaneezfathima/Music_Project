#include<iostream>
#include<fstream>
#include<unordered_map>
#include<vector>
#include<string>
#include </usr/include/boost/algorithm/string.hpp>
#include <utility>
#include <stdlib.h>

using namespace std;


void getSongForEachUser(unordered_map<int,set<int> > &usrToSngList, unordered_map<string,int> &my_userIDs,unordered_map<string,int> &my_songIDS,string fileName )
{

	ifstream f;
	f.open(fileName.c_str());

	if(!f)
	{
		cout<<"Error opening file"<<endl;
		return;
	}

	string line;
	while(getline(f,line))
	{

		vector<string> v;
		boost::split(v, line, boost::is_any_of("\t"));
		int uid;
		if( my_userIDs.find(v[0]) != my_userIDs.end()) 
		{
			uid=my_userIDs[v[0]];
			/*the user id is found from string*/
			/*check the user id in userToSngList hash table*/
			
			
			int sid;
			if(my_songIDS.find(v[1]) !=my_songIDS.end() )
			{
				sid=my_songIDS[v[1]];	
				//old user id with already set is pushed
				
								
					usrToSngList[uid].insert(sid);
			
			}
	
			
		}
	}

	f.close();
return;

}
