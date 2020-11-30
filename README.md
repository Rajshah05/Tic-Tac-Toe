# TIcTacToe

TicTacToe game in C++

To run the tic-tac-toe program compile using:

	g++ -std=c++14 -O1 main.cpp Tictactoe.cpp -o exec

then Run the tic-tac-toe game program using:
	./exec

Tested with Ubuntu g++ 7.8.5 on Ubuntu 18.04

Majority of the code is located in the Tictactoe files.

To test the program compile using:
	g++ -O1 catch_amalgamated.cpp test.cpp Tictactoe.cpp -o test

then run the test using:
	./test < testCases.txt
