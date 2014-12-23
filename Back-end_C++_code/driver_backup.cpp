#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include<set>
#include<algorithm>
#include <string>
#include "convertToID.h"
#include "eachUserSongList.h"
#include "songToUserList.h"
#include <utility>
#include "setIntersection.h"

using namespace std;

int main (int argc, char *argv[])
{

  string fileName;
//fileName="/home/shahnaz/kaggle_downloads/test100.txt";
  unordered_map < string, int >my_userIDs;
  unordered_map < string, int >my_songIDS;

  unordered_map < int, vector < pair < int, int > > >usrToSngList;
  unordered_map < int, set < int > >sngToUsrList;
  int totUsers = 0;
  int totSongs = 0;
  if (argc == 2)
    {
      cout << "called" << endl;
      fileName = argv[1];
      readFromFile (fileName, totUsers, totSongs, my_userIDs, my_songIDS);
      /*cout << "Total unique users :\t" << totUsers << endl;
      cout << "Total unique songs :\t" << totSongs << endl;
      cout << "-------------------------------------------------" << endl;
      cout << "SIze of hash of users" << my_userIDs.size () << endl;
      cout << "Size of hash of songs" << my_songIDS.size () << endl;
      unordered_map < string, int >::iterator it;
	
	for(it=my_userIDs.begin(); it!=my_userIDs.end();it++)
	{
		cout<< it->first <<": \t"<< it->second<<endl;
	}

	cout<<"size of hash of songs"<<my_songIDS.size()<<endl;

	for(it=my_songIDS.begin(); it!=my_songIDS.end();it++)
	{
		cout<< it->first <<": \t"<< it->second<<endl;
	}

	*/


	/*	getUserForEachSong (usrToSngList, my_userIDs, my_songIDS, fileName);


	//cout<< "SIZE of user to song list hash :\t" <<usrToSngList.size()<<endl;
	//check whether vector is properly inserted with song and count pair

	unordered_map< int,vector<pair< int,int > > > :: iterator ith;

	for(ith=usrToSngList.begin(); ith!=usrToSngList.end();ith++)
	{
		vector<pair< int,int > >:: iterator itv;
		cout<<ith->first<<":\t"<<endl;
		cout<<"============================================="<<endl;
		for(itv=(ith->second).begin(); itv!=(ith->second).end(); itv++)	
		{
			cout<<(*itv).first<<"\t" <<(*itv).second<<endl;
		}
		cout<<endl;
	}*/


     getSongForEachUser (sngToUsrList, my_userIDs, my_songIDS, fileName);
	
      cout << "SIZE of song to user list hash :\t" << sngToUsrList.size () << endl;

/*   unordered_map < int, set < int >>::iterator its;
      for (its = sngToUsrList.begin (); its != sngToUsrList.end (); its++)
	{
	  set < int >::iterator itv;
	  cout << its->first << ":\t" << endl;
	  cout << "=============================================" << endl;
	  for (itv = (its->second).begin (); itv != (its->second).end ();
	       itv++)
	    {
	      cout << *itv << "\t";
	    }
	  cout << endl;
	  cout << endl;
	}
cout<<"END of list formation"<<endl;*/


	/*call the set intersection */

    /*  unordered_map < int, set < int > >::iterator ity;
      unordered_map < int, set < int > >::iterator itx;

      unordered_map < int, vector < pair < int, int > > >sngSim;
      for (ity = sngToUsrList.begin (); ity != sngToUsrList.end (); ity++)
	{
	  for (itx = sngToUsrList.begin (); itx != sngToUsrList.end (); itx++)
	    {
	      if (ity->first != itx->first)
		{
		  set < int > res;
		  set < int > y = ity->second; 
		  set < int > x = itx->second; 
		  set_intersection (y.begin(),y.end(),x.begin(), x.end(), inserter(res,res.begin()));
		
		  int len = res.size ();

			if(len>0)
			{
			  pair < int, int >temp;
			  temp = make_pair (itx->first, len);
			  if (sngSim.find (ity->first) != sngSim.end ())
			    {
			      // song y is already present
			      sngSim[ity->first].push_back (temp);
			    }
			  else
			    {
			      // song y is new
			      vector < pair < int, int > > nwVec;
			      nwVec.push_back (temp);
			      sngSim[ity->first] = nwVec;
			    }
			}
		}

	    }
	}*/
      unordered_map < int, vector < pair < int, int > > >sngSim;
	getIntersection (sngSim,sngToUsrList);
	cout<<"size of song to song similarity hash"<<sngSim.size()<<endl;

/*print the song song similarity data structure*/
      unordered_map < int, vector < pair < int, int > > >:: iterator itss;
	cout<<"size of song to song similarity hash"<<sngSim.size()<<endl;
	for(itss=sngSim.begin(); itss!=sngSim.end();itss++)
	{
		cout<<"**************************************************"<<endl;
		cout<< itss->first <<": \t"<<endl;
		vector< pair<int,int> > :: iterator itssv;
		for(itssv=(itss->second).begin(); itssv!=(itss->second).end();itssv++)
		{
			cout<<(*itssv).first<<"\t" <<(*itssv).second<<endl;
		}
		cout<<"**************************************************"<<endl;
	cout<<endl;

	}

}
 else
{
      cout << "Please provide the location of file" << endl;
}
  return 0;
}
