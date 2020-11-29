#include "Tictactoe.h"
#include <memory>

int main() {
    std::unique_ptr<Tictactoe> game(new Tictactoe);
    game->play();
}