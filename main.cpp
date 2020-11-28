#include "Tictactoe.h"
#include <memory>

int main() {
    unique_ptr<Tictactoe> game(new Tictactoe);
    game->setGrid(3);
    game->displayGrid();
}