README for Program 3

Compiling and Running the Code:

1) A makefile has been included. Using "make 3" will compile only program 3, while "make" will compile all three programs.
2) The program is run as follows:
./program3 <filex.txt> <filey.txt> <output3.txt>

Data Structures:

A double vector of ints, LCSvals, is used to store the information for the table in the bottom-up approach. Its values are initialized to -1.

Computation Time:

This program runs somewhat faster than program 2, but the runtime is comparable. The additional speed for program 3 can be attributed to the memoization, which avoids unnecessary recursive computations for previously computed results.
