#include <iostream>
#include <fstream> //read / write to files
#include <algorithm> //max function
#include <chrono> //time
#include <vector>
#include <thread>
#include <string>

using namespace std;

//memoization vector for storing data
//all values initialized to -1
//LCSvals[i][j] is the LCS length for the ith prefix of X and the jth prefix of Y
static vector<vector<int>> LCSvals;

//returns the string for the first line of a text file
//filename must be a .txt or similar format, and must have extension
string getString(string filename){
  ifstream file; //holds the file object from fstream library
  file.open(filename);
  string str; //file contents are extracted here, then returned
  getline(file, str);
  return str;
}

//Bottom-Up Solution to the LCS problem
//outputs the length of the LCS of the two strings as an integer
//Takes in the two input strings, can be any length including 0
int lenLCS(string strx, string stry){
  int lenx = strx.length(); //length of first string
  int leny = stry.length(); //length of second string
  for(int j = 0; j <= leny; j++){
    for(int i = 0; i <= lenx; i++){
      if(i==0||j==0) LCSvals[i][j]=0;
      else{
        char charx = strx.at(i-1); //last character of first string
        char chary = stry.at(j-1); //last character of second string
        if(charx==chary) LCSvals[i][j]=LCSvals[i-1][j-1]+1;
        else LCSvals[i][j]=max(LCSvals[i][j-1], LCSvals[i-1][j]);
      }
    }
  }
  return LCSvals[lenx][leny];
}

//Produces the lcs of the two strings
//Must first have filled LCSvals
string lcs(string strx, string stry){
  string retval;
  int len1 = strx.length(); //length of the first string
  int len2 = stry.length(); //length of the second string
  while(len1>0 && len2>0){
    string charx = string(1, strx.at(len1-1));
    string chary = string(1, stry.at(len2-1));
    if(charx==chary){
      retval.insert(0, charx);
      len1--;
      len2--;
    }
    else if(LCSvals[len1-1][len2] > LCSvals[len1][len2-1]){
      len1--;
    }
    else{
      len2--;
    }
  }
  return retval;
}

int main(int argc, char **argv){
  string filex = argv[1]; //filename for first string
  string filey = argv[2]; //filename for second string
  string output = argv[3]; //output file

  //get the strings from the input files
  string strx = getString(filex); //first string
  string stry = getString(filey); //second string

  //initialize LCSvals
  for(unsigned int i = 0; i <= strx.length(); i++){
    vector<int> temp; //temporary 1D vector to be added as an element of the 2D vector LCSvals
    for(unsigned int j = 0; j <= stry.length(); j++){
      temp.push_back(-1);
    }
    LCSvals.push_back(temp);
  }

  //run the algorithm, and compute the time taken
  chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now(); //clock object from chrono library, time lenLCS starts
  int substrlen = lenLCS(strx, stry);
  chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //clock object from chrono library, time lenLCS ends
  auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start); //difference between start and end times
  //write to output2.txt
  ofstream file; //output file object
  file.open(output);
  //Output case for strings <= size 10
  if(strx.length()<=10 and stry.length()<=10){
    for(unsigned int i = 0; i <= strx.length(); i++){
      string s; //temp string for a line of the table to display
      for(unsigned int j = 0; j <= stry.length(); j++){
        s.append(to_string(LCSvals[i][j])+" ");
      }
      file << s << endl;
    }
    file << lcs(strx, stry) << endl;
  }
  //LCS length
  else file << substrlen << endl;
  //Running time
  if(time_taken.count()==0) file << "Less than 100 nanoseconds" << endl;
  else file << time_taken.count() << " nanoseconds"<< endl;
  file.close();
  return 0;
}
