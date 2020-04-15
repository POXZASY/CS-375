#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility> //pairs

using namespace std;


//stores the information needed for a knapsack problem
//weights and values are ordered and correspond by position
struct Problem{
  vector<int> weights; //weights of the items
  vector<int> values; //profits of the items
  int capacity; //total capacity
};

//stores the information for the solution to a knapsack problem
//weights and values are ordered and correspond by position
struct Solution{
  int totalitems; //total items in the problem
  int maxprofit; //profit achieved from optimal solution
  int solutionsize; //number of items in optimal solution
  int nodesvisited; //number of nodes visited
  int leavesvisited; //number of leaves visited
  vector<int> solweights; //weights for the solution items
  vector<int> solvalues; //values for the solution items
};

//stores the information needed for a single node in a tree for the knapsack problem traversal
struct Node{
  int level; //level of the node in the tree, base is 0
  int weight; //sum weight up to this point in the tree
  int profit; //sum profit up to this point in the tree
  int bound; //potential total value of the solution
  vector<bool> solution; //each bool represents the inclusion or exclusion of a single item. e.g. solution[1]==false means that this node is part of the solution that does not include item 2
};

//Priority queue for the knapsack problem
//addItem takes in a node object and a priority integer and adds the node to the queue accordingly
//popItem removes the highest priority node from the queue and returns that node
struct prioQueue{
  vector<pair<Node,int>> queue; //queue with priorities in increasing order
  void addItem(Node node, int prio){
    pair<Node,int> item; //stores the node and its priority
    item.first = node;
    item.second = prio;
    if(queue.size()==0) queue.push_back(item); //if queue is empty, adds node
    else if(queue[queue.size()-1].second < item.second) queue.push_back(item); //if new node is larger than all other nodes, adds to front
    //inserts node in queue with respect to priority
    else{
      for(unsigned int i = 0; i < queue.size(); i++){
        if(queue[i].second >= item.second){
          queue.insert(queue.begin()+i, item);
          break;
        }
      }
    }
  }
  Node popItem(){
    Node last = queue[queue.size()-1].first; //last item in the queue
    queue.pop_back();
    return last;
  }
};

//split a string, return the new strings as a vector
//str is string to split, splitter is the character to split by (in this case, comma is used)
vector<string> strsplit(string str, char splitter){
  vector<string> strs; //vector of strings, fills as string is split
  string tempstr = ""; //current string being populated by characters
  for(unsigned int i = 0; i < str.length(); i++){
    char currentchar = str.at(i); //current character being evaluated
    if(currentchar!=splitter) tempstr.append(string(1, currentchar));
    else{
      strs.push_back(tempstr);
      tempstr = "";
    }
  }
  if(tempstr!="" && tempstr!=string(1, splitter) && tempstr!=" ") strs.push_back(tempstr); //check for extra space at end of line
  return strs;
}

//returns a struct representing the 0-1 knapsack problem
//filename must be a .txt or similar format, and must have extension
Problem getProblem(string filename){
  Problem problem; //the problem to be returned
  ifstream file; //holds the file object from fstream library
  file.open(filename);
  int line = 0; //counts line being read
  Problem p; //temp struct for current problem
  string str; //temp string to hold current line content
  while(!file.eof()){
    getline(file, str);
    if(str.length()==0) break;
    line++;
    pair<int, int> nums; //the two numbers on this line of the string
    vector<string> numstrs = strsplit(str, ','); //the two strings returned by splitting by the comma
    nums.first = stoi(numstrs[0]); //the first number of the line
    nums.second = stoi(numstrs[1]); //the second number of the line
    if(line==1){
      problem.capacity = nums.second;
    }
    else{
      problem.weights.push_back(nums.first);
      problem.values.push_back(nums.second);
    }
  }
  return problem;
}

//function to return the upper bound on the value of the solution corresponding to this node in the knapsack tree
//takes in a node and the problem
int bound(Node node, Problem problem){
  int upperbound = node.profit;
  for(unsigned int i = node.level; i < problem.values.size(); i++){
    upperbound+=problem.values[i];
  }
  return upperbound;
}

//returns a struct representing the solution to the given problem using best-first-search with branch and bound
//takes in a problem object, formatted by getProblem
Solution getSolution(Problem problem){
  Solution solution; //the solution to be returned
  solution.totalitems = problem.weights.size();

  //node to represent the solution
  Node bestnode; //represents the final solution to the problem as a node in the tree
  bestnode.profit = 0;

  prioQueue Q; //priority queue for implementation of Best First Search
  Node u, v; //parent and child nodes for Best First Search implementation
  int maxprofit = 0; //maximum profit among traversed nodes in Best First Search
  v.level = 0;
  v.profit = 0;
  v.weight = 0;
  v.bound = bound(v, problem);
  Q.addItem(v, v.bound);
  int numnodes = 0; //tracks the total number of nodes traversed
  int numleaves = 0; //tracks the total number of leaves traversed

  while(Q.queue.size()>0){
    v = Q.popItem();
    numnodes++;
    if(v.weight > problem.capacity){
      numleaves++;
      continue;
    }
    if(v.profit >= bestnode.profit) bestnode = v;
    if(v.level==solution.totalitems){
      numleaves++;
      continue;
    }

    //any other nodes
    if(v.bound > maxprofit){
      u.level = v.level+1;

      //"yes" child
      u.weight = v.weight+problem.weights[u.level-1];
      u.profit = v.profit+problem.values[u.level-1];
      u.solution = v.solution;
      u.solution.push_back(true);
      if((u.weight<=problem.capacity) && (u.profit>maxprofit)){
        maxprofit = u.profit;
        bestnode = u;
      }
      u.bound = bound(u, problem);
      Q.addItem(u, u.bound);


      //"no" child
      u.weight = v.weight;
      u.profit = v.profit;
      u.bound = bound(u, problem);
      u.solution = v.solution;
      u.solution.push_back(false);
      Q.addItem(u, u.bound);
    }
    else{
      numleaves++;
    }
  }
  solution.maxprofit = bestnode.profit;
  solution.nodesvisited = numnodes;
  solution.leavesvisited = numleaves;
  for(unsigned int i = 0; i < bestnode.solution.size(); i++){
    if(bestnode.solution[i]){
      solution.solweights.push_back(problem.weights[i]);
      solution.solvalues.push_back(problem.values[i]);
    }
  }
  solution.solutionsize = solution.solweights.size();
  return solution;
}

//manages the file output
//takes in a solution to the knapsack problem and a filename, which should include the ".txt" extension
void outputSolution(Solution solution, string filename){
  ofstream file; //output file stream object
  file.open(filename);
  file << solution.totalitems << "," << solution.maxprofit << "," << solution.solutionsize << endl;
  file << solution.nodesvisited << "," << solution.leavesvisited << endl;
  for(int i = 0; i < solution.solutionsize; i++){
    file << solution.solweights[i] << "," << solution.solvalues[i] << endl;
  }
  file.close();
}

int main(int argc, char** argv){
  string input = argv[1]; //input file name
  string output = argv[2]; //output file name
  Problem problem = getProblem(input); //the knapsack problem
  Solution solution = getSolution(problem); //the solution to the knapsack problem
  outputSolution(solution, output);
  return 0;
}
