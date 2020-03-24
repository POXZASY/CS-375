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
//filename must be a .txt or similar format, and must have extension
string getString(string filename){
  ifstream file; //holds the file object from fstream library
  file.open(filename);
  string str; //file contents are extracted here, then returned
  getline(file, str);
  return str;
}

//Top-Down solution with memoization
//outputs the length of the LCS of the two strings as an integer
//Takes in the two input strings, can be any length including 0
int lenLCS(string strx, string stry){
  int lenx = strx.length(); //length of first string
  int leny = stry.length(); //length of second string
  //if i = 0 and j = 0
  if(lenx==0 || leny==0) {
    LCSvals[lenx][leny]=0;
    return 0;
  }
  //variables for other two cases
  string strx2 = strx.substr(0, strx.length()-1); //string x with last character removed
  string stry2 = stry.substr(0, stry.length()-1); //string y with last character removed
  int lenx2 = strx2.length(); //length of substring of first string w last char removed
  int leny2 = stry2.length(); //length of substring of second string w last char removed
  //if i,j > 0 and x_i = y_j
  int storedval = LCSvals[lenx2][leny2]; //length of the LCS of the strings with their last characters removed. -1 if not computed
  if(strx.at(lenx-1)==stry.at(leny-1)){
    //check if value has already been computed
    if(storedval>=0) return storedval+1;
    else{
      int temp = lenLCS(strx2, stry2); //length of LCS of the strings with their last characters removed
      LCSvals[lenx2][leny2]= temp;
      return temp+1;
    }
  }

  //if i,j > 0 and x_i != y_j
  int storedval1 = LCSvals[lenx][leny2]; //length of LCS of first string and second string without last character
  int storedval2 = LCSvals[lenx2][leny]; //length of LCS of first string without last
  int temp1, temp2; //temp values for the computation of the max function in the recursive solution.
  //temp1 is either the LCS of the already computed strx/stry2, or the LCS of the newly computed strx/stry2.
  //same applies to temp2

  if(storedval1>=0) temp1 = storedval1;
  else temp1 = lenLCS(strx, stry2);
  if(storedval2>=0) temp2 = storedval2;
  else temp2 = lenLCS(strx2, stry);
  return max(temp1, temp2);
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
  //LCS length
  file << substrlen << endl;
  //Running time
  if(time_taken.count()==0) file << "Less than 100 nanoseconds" << endl;
  else file << time_taken.count() << " nanoseconds"<< endl;
  file.close();
  return 0;
}
