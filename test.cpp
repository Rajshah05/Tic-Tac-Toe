#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "Tictactoe.h"
#include <memory>
#include <iostream>

std::unique_ptr<Tictactoe> game(new Tictactoe);
std::string result = game->play();
// std::cout << result << std::endl;

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