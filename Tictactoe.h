#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <vector>
#include <memory>

using namespace std;

class Tictactoe {
    private:
        int gridSize = 3;
        int numPlayers = 0;
        int turn = 1;
        int playerMove = 0;
        vector<vector<string>> grid;
        vector<int> computerMoves;
        vector<bool> filled;
    
    public:
        Tictactoe();
        void displayGrid();
        void setGrid(int grid_size);
};

#endif //TICTACTOE_H