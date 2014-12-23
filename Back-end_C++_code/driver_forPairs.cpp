#include <iostream>
#include <fstream>
#include "songToSongSImilarity1.h"

using namespace std;

int main (int argc, char *argv[])
{

  string newfileName,scoreFile;
  int uMin,uMax;
  if (argc == 5)
    {
    	newfileName=argv[1];
    	scoreFile=argv[2];
	uMin=stoi(argv[3]);
	uMax=stoi(argv[4]);
	writeSongScoresToFile(newfileName,scoreFile,uMin,uMax);

}
 else
{
      cout << "Please provide the location of file" << endl;
}
  return 0;
}
