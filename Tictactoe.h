#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <vector>
#include <memory>
#include <set>
#include <unordered_map>

class Tictactoe {
    private:
        int gridSize = 3;
        int numPlayers = 0;
        int turn = 1;
        int currentMove = 0;
        std::vector<std::vector<std::string>> grid;
        std::unordered_map<int, int> lineCountX;
        std::unordered_map<int, int> lineCountO;
        int filledCount = 0;
        
        void putMove(int Turn, int Move);
        int minimax(int);
        int findScore(int Turn);
        void setLineCount(int grid_size);
    
    public:
        Tictactoe();
        Tictactoe(int grid_size);
        void reset();
        void setGrid(int grid_size);
        void displayGrid();
        void setNumPlayers();
        int isComplete();
        void getOptimalMove(int Turn);
        void putMove();
        void removeMove(int Move, int Turn);
        bool isMoveValid();
        void changeTurn();
        void getUserMove();
        bool isFilled(int Move);
        std::string play();
};

#endif //TICTACTOE_H