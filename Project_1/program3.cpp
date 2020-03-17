#include <iostream>
#include <fstream> //read / write to files
#include <algorithm> //max function
#include <chrono> //time
#include <vector>

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

//Top-Down solution with memoization
int lenLCS(string strx, string stry){
  int lenx = strx.length();
  int leny = stry.length();
  //if i = 0 and j = 0
  if(lenx==0 || leny==0) {
    LCSvals[lenx][leny]=0;
    return 0;
  }
  //variables for other two cases
  string strx2 = strx.substr(0, strx.length()-1); //string x with last character removed
  string stry2 = stry.substr(0, stry.length()-1); //string y with last character removed
  int lenx2 = strx2.length();
  int leny2 = stry2.length();
  //if i,j > 0 and x_i = y_j
  int storedval = LCSvals[lenx2][leny2];
  if(strx.at(lenx-1)==stry.at(leny-1)){
    //check if value has already been computed
    if(storedval>=0) return storedval+1;
    else{
      int temp = lenLCS(strx2, stry2);
      LCSvals[lenx2][leny2]= temp;
      return temp+1;
    }
  }

  //if i,j > 0 and x_i != y_j
  int storedval1 = LCSvals[lenx][leny2];
  int storedval2 = LCSvals[lenx2][leny];
  int temp1, temp2;

  if(storedval1>=0) temp1 = storedval1;
  else temp1 = lenLCS(strx, stry2);
  if(storedval2>=0) temp2 = storedval2;
  else temp2 = lenLCS(strx2, stry);
  return max(temp1, temp2);
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
