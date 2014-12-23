#include<iostream>
#include<fstream>
#include<unordered_map>
#include<vector>
#include<string>
#include </usr/include/boost/algorithm/string.hpp>
#include <utility>
#include <stdlib.h>

using namespace std;


void getSongList(unordered_map<int,set<int> > &t_usrToSngList, unordered_map<string,int> &t_my_userIDs,unordered_map<string,int> &t_my_songIDS,string &testData )
{

	ifstream f;
	f.open(testData.c_str());

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
		if( t_my_userIDs.find(v[0]) != t_my_userIDs.end()) 
		{
			uid=t_my_userIDs[v[0]];
			/*the user id is found from string*/
			/*check the user id in userToSngList hash table*/
			
			
			int sid;
			if(t_my_songIDS.find(v[1]) !=t_my_songIDS.end() )
			{
				sid=t_my_songIDS[v[1]];	
				//old user id with already set is pushed
				
								
					t_usrToSngList[uid].insert(sid);
			
			}
	
			
		}
	}

	f.close();
return;

}
