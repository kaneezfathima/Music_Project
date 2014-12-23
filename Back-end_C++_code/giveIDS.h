#include<iostream>
#include<fstream>
#include<unordered_map>
#include<vector>
#include<string>
#include </usr/include/boost/algorithm/string.hpp>

using namespace std;


/*reads each line from the file: splits at tab
  converts each user id string into interger 
  converts each song id string into interger 
*/

void readFromTestFile(string &testData, int &totUsers, int &totSongs,unordered_map<string,int> &t_my_userIDs,unordered_map<string,int> &t_my_songIDS,unordered_map < int, string > &t_userIDs_to_str,unordered_map < int, string > &t_songIDS_to_str,unordered_map < string, int > &my_userIDs,unordered_map < string, int > &my_songIDS){
	
	ifstream f;
	f.open(testData.c_str());
	if(!f)
	{
		cout<<"Error opening file:"<<testData<<endl;
		return;
	}

	string line;
	int uCount=1;int sCount=1;
	while(getline(f,line))
	{

		vector<string> v;
		boost::split(v, line, boost::is_any_of("\t"));
		if(t_my_userIDs.find(v[0]) == my_userIDs.end()) 
		{
			/*add new user and increment id*/
			t_my_userIDs[v[0]]=uCount;
			t_userIDs_to_str[uCount]=v[0];
			uCount++;
		}
		
		if(my_songIDS.find(v[1]) ==my_songIDS.end())
		{
			/*add new user and increment id*/
			t_my_songIDS[v[1]]=sCount;
			t_songIDS_to_str[sCount]=v[1];
			sCount++;
		}
	}

	f.close();
	totUsers=uCount;
	totSongs=sCount;
return;
}
