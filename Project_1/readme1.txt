README for Program 1

Compiling and Running the Code:

1) A makefile has been included. Using "make1" will compile only program 1, while "make" will compile all three programs.
2) The program is run as follows:
./program1 <filex.txt> <filey.txt> <output1.txt>

Data Structures:

A double vector of ints, LCSvals, is used to store the information for the table in the bottom-up approach. Its values are initialized to -1.

Computation Time:

This program runs extremely quickly, as the function that implements the bottom-up algorithm, lenLCS, has no recursive calls but iterates through the vector. I used the chrono library to time the function, but was only able to get an accuracy to the nearest 100 nanoseconds. Chrono reports a time of 0, implying that the function completes in under 100 nanoseconds, which is very fast. I suspect if I wrote this function to depend on recursive calls, it would be slower like the other two programs.
