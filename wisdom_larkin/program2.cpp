#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;

//returns the string for the first line of a text file
//filename must be a .txt or similar format, and must have extension
string getString(string filename){
  ifstream file; //holds the file object from fstream library
  file.open(filename);
  string str; //file contents are extracted here, then returned
  getline(file, str);
  return str;
}

//Recursive solution without memoization
//outputs the length of the LCS of the two strings as an integer
//Takes in the two input strings, can be any length including 0
int lenLCS(string strx, string stry){
  int lenx = strx.length(); //length of first string
  int leny = stry.length(); //length of second string
  if(lenx==0 || leny==0) return 0;
  string strx2 = strx.substr(0, strx.length()-1); //string x with last character removed
  string stry2 = stry.substr(0, stry.length()-1); //string y with last character removed
  if(strx.at(lenx-1)==stry.at(leny-1)) return lenLCS(strx2, stry2)+1;
  return max(lenLCS(strx, stry2), lenLCS(strx2, stry));
}

int main(int argc, char **argv){
  string filex = argv[1]; //filename for first string
  string filey = argv[2]; //filename for second string
  string output = argv[3]; //output file

  //get the strings from the input files
  string strx = getString(filex); //first string
  string stry = getString(filey); //second string

  //run the algorithm, and compute the time taken
  chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now(); //clock object from chrono library, time lenLCS starts
  int substrlen = lenLCS(strx, stry);
  chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //clock object from chrono library, time lenLCS ends
  auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start); //difference between start and end times
  //write to output2.txt
  ofstream file; //output file object
  file.open(output);
  //LCS length
  file << substrlen << endl;
  //Running time
  if(time_taken.count()==0) file << "Less than 100 nanoseconds" << endl;
  else file << time_taken.count() << " nanoseconds"<< endl;
  file.close();
  return 0;
}
