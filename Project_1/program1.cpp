#include <iostream>
#include <fstream> //read / write to files
#include <algorithm> //max function
#include <chrono> //time
#include <vector>
#include <thread>

using namespace std;

//memoization vector for storing data
//all values initialized to -1
//LCSvals[i][j] is the LCS length for the ith prefix of X and the jth prefix of Y
static vector<vector<int>> LCSvals;

//returns the string for the first line of a text file
string getString(string filename){
  ifstream file;
  file.open(filename);
  string str;
  getline(file, str);
  return str;
}

//Bottom-Up Solution
int lenLCS(string strx, string stry){
  std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  int lenx = strx.length();
  int leny = stry.length();
  for(int j = 0; j <= leny; j++){
    for(int i = 0; i <= lenx; i++){
      if(i==0||j==0) LCSvals[i][j]=0;
      else{
        char charx = strx.at(i-1);
        char chary = stry.at(j-1);
        if(charx==chary) LCSvals[i][j]=LCSvals[i-1][j-1]+1;
        else LCSvals[i][j]=max(LCSvals[i][j-1], LCSvals[i-1][j]);
      }
    }
  }
  return LCSvals[lenx][leny];
}

int main(int argc, char **argv){
  string filex = argv[1];
  string filey = argv[2];
  string output = argv[3];
  //get the strings from the input files
  string strx = getString(filex);
  string stry = getString(filey);
  //initialize LCSvals
  for(unsigned int i = 0; i <= strx.length(); i++){
    vector<int> temp;
    for(unsigned int j = 0; j <= stry.length(); j++){
      temp.push_back(-1);
    }
    LCSvals.push_back(temp);
  }

  //run the algorithm, and compute the time taken
  chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  int substrlen = lenLCS(strx, stry);
  chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
  //chrono::duration<double> time_taken = chrono::duration_cast<chrono::duration<double>>(end-start);
  auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
  //write to output2.txt
  ofstream file;
  file.open(output);
  //Output case for strings <= size 10
  if(strx.length()<=10 and stry.length()<=10){
    for(unsigned int i = 0; i <= strx.length(); i++){
      string s;
      for(unsigned int j = 0; j <= stry.length(); j++){
        s.append(to_string(LCSvals[i][j])+" ");
      }
      file << s << endl;
    }
  }
  //LCS length
  file << substrlen << endl;
  //Running time
  if(time_taken.count()==0) file << "Less than 100 nanoseconds" << endl;
  else file << time_taken.count() << " nanoseconds"<< endl;
  file.close();
  return 0;
}
