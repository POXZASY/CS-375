README

Compiling and Running the Code:

1) A makefile has been included. Using "make" will compile the code.
2) The program is run as follows:
./BestFirstSearch <input.txt> <output.txt>

Data Structures:

There were four major data structures used in the implementation of this assignment, all of them structs. The "Problem" and "Solution" structs held the information needed to solve the knapsack problem. The Problem struct holds only sorted weights and values for the items in the problem, and the capacity is stored as well. The Solution struct also holds weights and values for items, but only the solution items. It stores the rest of the necessary information to be output for the solution as well.
For the Best First Search implementation with branch and bound, the knapsack tree is represented with a priority queue struct and a node struct. The priority queue has a vector of pairs which hold a node and an int. The int represents the priority of the node. The priority queue also has two functions, one which adds to the queue and one which removes the highest priority value from the queue. The node holds information about the total weight and profit up to that depth in the tree. It holds the level of the node, as well as the potential upper bound on the return for a solution stemming from that node. Critically, it holds a vector of bools. The bools correspond to whether or not items are to be included in a solution involving that node. For example, solution[2]=false implies that a solution for that node does not include the third item.

Computation Time:

Reading every node in a tree can take up to 2^n time for n items, but with branch and bound limiting the number of searches, the search should be significantly faster than this on average. Nevertheless, we can take O(2^n) as a worst-case for this algorithm.

Classes:

No classes were used in this program.
