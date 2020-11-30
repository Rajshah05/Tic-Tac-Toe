#include "Tictactoe.h"
#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<Tictactoe> game(new Tictactoe);
    std::string result = game->play();
    std::cout << result << std::endl;
    game->reset();
}