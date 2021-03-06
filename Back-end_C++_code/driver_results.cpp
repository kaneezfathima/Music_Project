#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <utility>
#include "convertToID.h"
#include "eachUserSongList.h"
#include "songToSongSImilarity1.h"
#include "writeSongSongPairToFile.h"
#include "songToUserList.h"
#include "cosineSimilarity.h"
#include "userCount.h"
//#include "aggregate.h"
#include "processTestData.h"

using namespace std;

int main (int argc, char *argv[])
{

  string fileName,newfileName,scoreFile,latestSongs;
//fileName="/home/shahnaz/kaggle_downloads/test100.txt";
unordered_map < string, int >my_userIDs;  
unordered_map < int, string >userIDs_to_str;
unordered_map < string, int >my_songIDS; 
unordered_map < int, string >songIDS_to_str;

  unordered_map < int, set <int> >usrToSngList;
  unordered_map < int, set < int > >sngToUsrList;
  int totUsers = 0;
  int totSongs = 0;
  int uMin,uMax,N;
  if (argc == 4)
    {
        fileName = argv[1];//Name of triplet file, to convert into ids, in "convertToID.h"
	readFromFile (fileName, totUsers, totSongs, my_userIDs, my_songIDS,userIDs_to_str,songIDS_to_str);
  
     	scoreFile=argv[2];

	N=stoi(argv[3]);

     // getSongForEachUser (usrToSngList, my_userIDs, my_songIDS, fileName);
	//writeSongPairsToFile(usrToSngList,newfileName);
	
	/*reads from newfileName in "songToSongSImilarity1.h", writes to scoreFile
		newfileName file contains: songID1	songID2
	*/
	//writeSongScoresToFile(newfileName,scoreFile,uMin,uMax);

        getUsersForEachSong (sngToUsrList, my_userIDs, my_songIDS, fileName);

	
 
/*
Now calulate the cosine similarity

1) get the count of users for each song from "sngToUsrList", store it in new hash table(singid, number of users) "usrLen"
2) read from file the scores from "sngSim". The score is our numerator
3) for each pair of songs calculate: score/((len(song1)^alpha)*(len(song2)^(1-alpha))), store it in another hash table(songid, <songid,value>)

*/
unordered_map < int,int> usrLen;

getLen(sngToUsrList,usrLen);

unordered_map < int, set < pair < int, double > > > cosineSim;

/*to calulte cosine similarity, in cosineSimilarity.h*/
double alpha=0.5; double q=1;
findCosSim(cosineSim,usrLen,scoreFile,alpha,q);

/*send the test data to processTestData.h file method*/
convertTestData(cosineSim,N,my_userIDs, my_songIDS);

}
 else
{
      cout << "Please provide the location of file..." << endl;
}
  return 0;
}
