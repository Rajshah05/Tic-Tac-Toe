#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <vector>
#include <memory>
#include <set>

class Tictactoe {
    private:
        int gridSize = 3;
        int numPlayers = 0;
        int turn = 1;
        int playerMove = 0;
        std::vector<std::vector<std::string>> grid;
        std::vector<int> computerMoves;
        std::vector<bool> filled;
        
        bool checkCrossed(std::set<std::string> line);
    
    public:
        Tictactoe();
        void setGrid(int grid_size);
        void displayGrid();
        void setNumPlayers();
        int isComplete();
};

#endif //TICTACTOE_H