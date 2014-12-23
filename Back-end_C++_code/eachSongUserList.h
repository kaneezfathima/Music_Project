#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include </usr/include/boost/algorithm/string.hpp>
#include <utility>
#include <stdlib.h>
#include <unordered_set>
#include<unordered_map>
using namespace std;
void getSongForEachUser(unordered_map<int,unordered_set<int> > &sngToUsrList, unordered_map<string,int> &my_userIDs,unordered_map<string,int> &my_songIDS,string fileName);

void getSongForEachUser(unordered_map<int,unordered_set<int> > &sngToUsrList, unordered_map<string,int> &my_userIDs,unordered_map<string,int> &my_songIDS,string fileName)
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
		int sid;
		if( my_songIDS.find(v[1]) != my_songIDS.end()) 
		{
			sid=my_songIDS[v[1]];
			/*the song id is found from string*/
			/*check the song id in sngToUsrList hash table*/
			
			
			if(sngToUsrList.find(sid) != sngToUsrList.end()) 
			{
				int uid;
				if(my_userIDs.find(v[0]) !=my_userIDs.end() )
				{
					uid=my_userIDs[v[0]];	
					//old song id is already inserted in the set
					

						sngToUsrList[sid].insert(uid);
				
					
				}
			}
			else
			{
				/*if the song is new, push the songid with the new user set as key*/	
				unordered_set<int> nwVec;
				pair<int,int> temp;
				int uid;
				if(my_userIDs.find(v[0]) !=my_userIDs.end())
				{
					uid=my_userIDs[v[0]];	
					nwVec.insert(uid);
					sngToUsrList[sid]=nwVec;		
				}			
			}

		}
	}

	f.close();
return;

}
