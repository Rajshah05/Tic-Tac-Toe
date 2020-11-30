# TIcTacToe

TicTacToe game in C++

Uses minimax algorithm in game theory to find optimal move

Majority of the code is located in the Tictactoe files.

"play" member function uses all the member functions to run a tic-tac-toe game

"isComplete" member function checks if any row, collumn or diagonal is completed. It aslo checks if all the cells are filled and therefore if game is draw

"getOptimalMove" member function finds optimal move using minimax algorithm which is a backtracking algorithm that recursively places move on all the possible cells and calculates score for each move

"setGrid" member function creates a grid (board) of desired size

"reset" member function resets all the data members to initial condition


To run the tic-tac-toe program compile using:

	g++ -std=c++14 -O1 main.cpp Tictactoe.cpp -o exec

then Run the tic-tac-toe game program using:

	./exec

Tested with Ubuntu g++ 7.8.5 on Ubuntu 18.04

generated test cases to test the tic-tac-toe program

Used Catch2 framework to write test cases

To run the test cases compile the test file using:

	g++ -O1 catch_amalgamated.cpp test.cpp Tictactoe.cpp -o test

then run the test using:

	./test < testCases.txt



