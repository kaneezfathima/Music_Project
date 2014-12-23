#include<iostream>
#include<fstream>
#include<vector>
#include<string>
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

void aggregateFn(unordered_map < int, set < pair < int, double > > > &cosineSim,unordered_map < int, set <int> > &t_usrToSngList,unordered_map < int, vector<pair<int,double> > > &predictionList)
{
	
	
	unordered_map < int, set <int> >::iterator it1; //cout<<"usrtoSnglist\t"<<t_usrToSngList.size()<<endl;
	for(it1=t_usrToSngList.begin();it1!=t_usrToSngList.end();it1++)
	{
		set<int> sTemp;
		int uid=it1->first;
		set <int>::iterator it2;
		for(it2=(it1->second).begin();it2!=(it1->second).end();it2++)		
		{
			sTemp.insert(*it2);
		}
		
		/*take each element from sTemp and find out the list from cosineSim set, push them into vector*/
		set<int>::iterator it;
		vector <pair< int, double >> totalSngs;
		for(it=sTemp.begin(); it!=sTemp.end();it++)
		{
			int sid=*it;
			if(cosineSim.find(sid)!=cosineSim.end())
			{

				set< pair < int, double > >::iterator it1;
				set< pair < int, double > > l=cosineSim[sid];
				for(it1=l.begin(); it1!=l.end();it1++)
				{
					if(sTemp.find((*it1).first)==sTemp.end()){
						totalSngs.push_back(make_pair((*it1).first,(*it1).second));
						//cout<<	"inside...."<<totalSngs.size()<<endl;
					}
				}
			
			}
		}
		/*Now loop through the totalSngs which has lists of songs, push the elements in unordered_map(key, score)
		Now sort the map, based on scores, based on 'N' , pick up the top-N elements 	
		*/
		if(totalSngs.size()>0){//cout<<"total:\t"<<totalSngs.size()<<endl;
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
		vector<pair<int,double> > vPair;		
		for(ith=hmap.begin(); ith!=hmap.end();ith++)
		{
			vPair.push_back(make_pair(ith->first,ith->second));
		}
		sort(vPair.begin(),vPair.end(),compFn);

		predictionList.insert(make_pair(uid,vPair));

		}
	}
}

