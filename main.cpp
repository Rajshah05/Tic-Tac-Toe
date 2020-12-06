#include "Tictactoe.h"
#include <memory>
#include <iostream>

int main() {
    Tictactoe game;
    std::string result = game.play();
    std::cout << result << std::endl;
    game.reset();
}