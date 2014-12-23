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

void findCosSim(unordered_map < int, set < pair < int, double > > > &cosineSim,
unordered_map < int,int> &usrLen,
string &scoreFile, double &alpha, double &q);

void calculate(int &sid1,int &sid2,double &num,unordered_map < int, set < pair <int, double > > > &cosineSim,
unordered_map < int,int> &usrLen, double &alpha, double &q);


void findCosSim(unordered_map < int, set < pair < int, double > > > &cosineSim,
unordered_map < int,int> &usrLen,
string &scoreFile, double &alpha, double &q)
{
	ifstream f;
	f.open(scoreFile.c_str());

	if(!f)
	{
		cout<<"Error opening file"<<endl;
		return;
	}

	string line;
	while(getline(f,line))
	{
		vector<string> v,v1,v2;
		boost::split(v, line, boost::is_any_of("\t"));
	/*	now we get v[0]= songid1
		v[1]= list of all related songs(songid2,score)*/
		if(v.size()==2){	
			int sid1=atoi(v[0].c_str());
		
			vector<string>::iterator itv;
		
			/* iterate through the list and get each pair for calculation	
	
			now split v[1] at ','	*/
			string s1=v[1];		
			boost::split(v1, s1, boost::is_any_of(","));	
			for(itv=v1.begin();itv!=v1.end();itv++)
			{
				string s2=*itv;
				boost::split(v2, s2, boost::is_any_of(":"));
				if(v2.size()>1)
				{
				int sid2   = atoi(v2[0].c_str());
				double num =atoi(v2[1].c_str());
				calculate(sid1,sid2,num,cosineSim,usrLen, alpha,q);
				}
			}	
		}
	}
f.close();
//cout<<"end...."<<endl;
return;
}

void calculate(int &sid1,int &sid2,double &num,unordered_map < int, set < pair < int, double > > > &cosineSim,
unordered_map < int,int> &usrLen, double &alpha, double &q)
{
 
int len1=usrLen[sid1];
int len2=usrLen[sid2];

//cout<<"len1:"<<len1<<endl;
//cout<<"len2:"<<len2<<endl;
double den=pow(len1,alpha)*pow(len2,(1-alpha));
/*cout<<"den:"<<den<<endl;
cout<<"num:"<<num<<endl;*/
double res=num/den;

// find the power of the result with "q"

res=pow(res,q);

// now insert these values in the "cosineSim"

pair < int, double > temp;

temp=make_pair(sid2,res);
//cout<<temp.first<<"|"<<temp.second<<endl;
cosineSim[sid1].insert(temp);

return;
}
