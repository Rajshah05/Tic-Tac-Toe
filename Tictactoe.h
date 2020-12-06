#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <vector>
#include <memory>
#include <set>
#include <unordered_map>

struct position
{
    int row;
    int col;
};

class Tictactoe {
    private:
        int gridSize;
        int numPlayers;
        int turn;
        int currentMove;
        std::vector<std::vector<std::string>> grid;
        std::unordered_map<int, std::unordered_map<int, int>> lineCount;
        int filledCount;
        
        int minimax(int);
        int findScore(int Turn);
        void setLineCount(int grid_size);
        void updateLineCount(int Turn, bool isIncrement, position pos);
    
    public:
        Tictactoe();
        Tictactoe(int grid_size);
        void reset();
        void setGrid(int grid_size);
        void displayGrid();
        void setNumPlayers();
        int isComplete();
        void putMove(int Turn, int Move);
        void getOptimalMove(int Turn);
        void removeMove(int Move, int Turn);
        bool isMoveValid();
        void changeTurn();
        void getUserMove();
        bool isFilled(int Move);
        position moveToPosition(int Move);
        std::string play();
};

#endif //TICTACTOE_H