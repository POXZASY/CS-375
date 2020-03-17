#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;

//returns the string for the first line of a text file
string getString(string filename){
  ifstream file;
  file.open(filename);
  string str;
  getline(file, str);
  return str;
}

//Recursive solution without memoization
int lenLCS(string strx, string stry){
  int lenx = strx.length();
  int leny = stry.length();
  if(lenx==0 || leny==0) return 0;
  string strx2 = strx.substr(0, strx.length()-1); //string x with last character removed
  string stry2 = stry.substr(0, stry.length()-1); //string y with last character removed
  if(strx.at(lenx-1)==stry.at(leny-1)) return lenLCS(strx2, stry2)+1;
  return max(lenLCS(strx, stry2), lenLCS(strx2, stry));
}

int main(int argc, char **argv){
  string filex = argv[1];
  string filey = argv[2];
  string output = argv[3];
  //get the strings from the input files
  string strx = getString(filex);
  string stry = getString(filey);
  //run the algorithm, and compute the time taken
  chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  int substrlen = lenLCS(strx, stry);
  chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
  chrono::duration<double> time_taken = chrono::duration_cast<chrono::duration<double>>(end-start);
  //write to output2.txt
  ofstream file;
  file.open(output);
  file << substrlen << endl;
  if(time_taken.count()==0) file << "Less than 100 nanoseconds" << endl;
  else file << time_taken.count() << " seconds"<< endl;
  file.close();
  return 0;
}
