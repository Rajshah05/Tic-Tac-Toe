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
        int currentMove = 0;
        std::vector<std::vector<std::string>> grid;
        std::vector<bool> filled;
        
        bool checkCrossed(std::set<std::string> line);
        void putMove(int tempTurn, int tempMove);
        int minimax(int);
        int findScore(int tempTurn);
    
    public:
        Tictactoe();
        void setGrid(int);
        void displayGrid();
        void setNumPlayers();
        int isComplete();
        int optimalComputerMove(int);
        void putMove();
        void removeMove(int);
        bool isMoveValid();
        void changeTurn();
        std::string play();
};

#endif //TICTACTOE_H