README for Program 2

Compiling and Running the Code:

1) A makefile has been included. Using "make2" will compile only program 2, while "make" will compile all three programs.
2) The program is run as follows:
./program2 <filex.txt> <filey.txt> <output2.txt>

Computation Time:

This program runs the slowest, a little bit slower than program 3. This is expected, as the lenLCS function makes many recursive calls, and repeats operations that have been previously computed, which is optimized in program 3.
