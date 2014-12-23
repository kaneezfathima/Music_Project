#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include </usr/include/boost/algorithm/string.hpp>
#include <utility>
#include <stdlib.h>
#include <set>
#include<unordered_map>
#include <math.h>
using namespace std;

/*aggregation */
/*Read from "latestSongs" file */

bool compFn(pair<int,double> a,pair<int,double> b)
{
	return (a.second > b.second);
}

void aggregate(unordered_map < int, set < pair < int, double > > > &cosineSim,string &latestSongs,vector<pair<int,double>> &vPair)
{
	
	set<string> sTemp;
	ifstream f;
	f.open(latestSongs.c_str());

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
		sTemp.insert(v[0]);
	}
	/*take each element from sTemp and find out the list from cosineSim set, push them into vector*/
	set<string>::iterator it;
	vector <pair< int, double >> totalSngs;
	for(it=sTemp.begin(); it!=sTemp.end();it++)
	{
		int sid=stoi(*it);
		if(cosineSim.find(sid)!=cosineSim.end())
		{

			set< pair < int, double > >::iterator it1;
			set< pair < int, double > > l=cosineSim[sid];
			for(it1=l.begin(); it1!=l.end();it1++)
			{
				totalSngs.push_back(make_pair((*it1).first,(*it1).second));	
			}
			
		}
	}
	/*Now loop through the vList which has lists of songs, push the elements in unordered_map(key, score)
	Now sort the map, based on scores, based on 'N' , pick up the top-N elements 	
	*/
	unordered_map<int, double> hmap;
	vector < pair<int, double> > ::iterator itv;
	for(itv=totalSngs.begin(); itv!=totalSngs.end();itv++)
	{
			
		if(hmap.find(itv->first)!=hmap.end())
		{
			/*if already in the map, upadate the score*/
			hmap[itv->first]+=itv->second;
		}
		else{
			/*first time inserstion in the map*/
			hmap[itv->first]=itv->second;
		}
			
	}
	
	
	unordered_map<int, double>::iterator ith;
	for(ith=hmap.begin(); ith!=hmap.end();ith++)
	{
		vPair.push_back(make_pair(ith->first,ith->second));
	}
	sort(vPair.begin(),vPair.end(),compFn);
}

