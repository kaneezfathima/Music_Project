#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include<math.h>

using namespace std;
double sendCalculate(vector<bool> &presentOrNot,vector<double> &pie);

void calPrecision(unordered_map < int, vector<pair<int,double> > > &predictionList,string &hiddenFile,unordered_map < string, int > &t_my_userIDs,unordered_map < string, int > &t_my_songIDS,unordered_map < int, string > &t_userIDs_to_str,unordered_map < int, string > &t_songIDS_to_str, int &N)
{

	ifstream f1;

	f1.open(hiddenFile.c_str());
	if(!f1)
	{
		cout<<"Error opening file:"<<hiddenFile<<endl;
		return;
	}

	/*Read from hidden file
	=======================
	1) generate user to song list :unordered_map < int, set <int> > hiddenUsr_To_SngList

	calculate precision
	=========================
	predictionList: userID,songlIst
	for each user from the predictionList, get the corresponding song list in "hiddenUsr_To_SngList".  
	*/
	unordered_map < int, set <int> > hiddenUsr_To_SngList;
	string line;
	//cout<<"sz u:"<<t_my_userIDs.size()<<endl;
	//cout<<"sz s:"<<t_my_songIDS.size()<<endl;
	while(getline(f1,line))
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
				hiddenUsr_To_SngList[uid].insert(sid);
			
			}
	
			
		}
	}

	f1.close();
	//cout<<"aftr...fclose"<<endl;
	unordered_map < int, set <int> >::iterator it;//hiddenUsr_To_SngList(uid,[set]listof songs)
	unordered_map < int, vector<pair<int,double> > >::iterator itv;// &predictionList(uid,[vector]listofsongs)
	double totalPrecision=0; int totalUsers=0;
	for(itv=predictionList.begin();itv!=predictionList.end();itv++)
	{
		if(hiddenUsr_To_SngList.find(itv->first)!=hiddenUsr_To_SngList.end())
		{
			/*get the list from predictionList, 
			search in hiddenUsr_To_SngList[uid] 
			if the user listened or not*/
			vector<pair<int,double> > vtemp=(itv->second);
			vector<pair<int,double> >::iterator itv1;
			vector<bool> presentOrNot;
			vector<double> pie;
			double currentSum=0; 
			for(itv1=(vtemp).begin();itv1!=(vtemp).end();itv1++)
			{
				if(t_songIDS_to_str.find(itv1->first)!=t_songIDS_to_str.end() )
				{
					if(presentOrNot.size()<N)
					{
						if(hiddenUsr_To_SngList[itv->first].find(itv1->first)==hiddenUsr_To_SngList[itv->first].end())
						{
							//song is not present
							presentOrNot.push_back(false);
						}
						else
						{
							//song is not present
							presentOrNot.push_back(true);
							currentSum++;

						}
							pie.push_back(currentSum/(pie.size()+1));		
					}
					else 
					{
						break;
					}
					
				}
			}
			/*call calculate Precision funcion*/
			double sumVal=sendCalculate(presentOrNot,pie);
			totalPrecision+=sumVal;
		}
	totalUsers++;
	}	
/*Total mean average precision*/

double meanAvgPrecision=totalPrecision/totalUsers;

cout<<"Total precision:\t"<<totalPrecision<<endl;
cout<<"MAP:\t"<<meanAvgPrecision<<endl;
cout<<"Total users :\t"<<totalUsers<<endl;
cout<<"Prediction List size:\t"<<predictionList.size();
return;
}

double sendCalculate(vector<bool> &presentOrNot,vector<double> &pie)
{
	double s=0; double summation=0;
	for(int i=0; i<presentOrNot.size();i++)
	{
		if(presentOrNot[i])
		{
			/*true*/
			summation+=pie[i]*1;		
		}
	}
	//cout<<"N val:\t"<<presentOrNot.size()<<endl;
	return (summation/presentOrNot.size());
}

