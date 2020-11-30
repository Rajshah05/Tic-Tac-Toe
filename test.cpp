#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "Tictactoe.h"
#include <memory>
#include <iostream>

// This file runs testcases by taking inputs from an external file "testCases.txt"

// The format of input is:

// first integer (1/2) represents single player game or double player game respectively

// if it is a sigle player game then the subsequent lines represent player 1 moves. computer plays deterministically

// if it is a double player game then the subsequent lines represent player 1 moves (X) and player 2 moves (O)
// alternatively starting with player 1 moves 

// Three test cases are designed each having 4 assertions

// First test case is tested for single player games and the games finish with a draw
// Second test case is tested for single player games and computer wins
// Third test case is tested for double player games and player 2 wins

// All of these test cases covers all the lines (rows, columns, and diagonals) getting completed
// i.e. three X or O for gridSize 3
std::unique_ptr<Tictactoe> game(new Tictactoe);

TEST_CASE("tictactoe game is played optimally against computer", "[draw][single player]") {
    REQUIRE(game->play() == "Match Draw");
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Match Draw");
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Match Draw");
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Match Draw");
}

TEST_CASE("tictactoe game is played against computer and computer wins", "[p2 wins][single player]") {
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Player 2 wins!!!");
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Player 2 wins!!!");
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Player 2 wins!!!");
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Player 2 wins!!!");
}

TEST_CASE("tictactoe game is played against human, [double player]") {
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Player 1 wins!!!");
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Player 1 wins!!!");
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Player 1 wins!!!");
    game->reset();
    game->setGrid(3);
    REQUIRE(game->play() == "Player 1 wins!!!");
}