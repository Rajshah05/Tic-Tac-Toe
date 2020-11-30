#include "Tictactoe.h"
#include <iostream>
#include <unordered_map>
#include <set>

Tictactoe::Tictactoe() {
    setGrid(3);
    setLineCount(3);
}

Tictactoe::Tictactoe(int grid_size) {
    setGrid(grid_size);
    setLineCount(grid_size);

}

// resets the data members to initial conditions
void Tictactoe::reset() {
    numPlayers = 0;
    turn = 1;
    currentMove = 0;
    filledCount = 0;
    setLineCount(gridSize);
}

// creates a grid (board) of size grid_size
void Tictactoe::setGrid(int grid_size) {
    auto n = 1;
    gridSize = grid_size;
    grid = std::vector<std::vector<std::string>> (gridSize, std::vector<std::string>(gridSize));
    for(auto& i : grid) {
        for(auto& j : i) {
            if(n < 10) {
                j = "0"+std::to_string(n);
            } else {
                j = std::to_string(n);
            }
            n++;
        }
    }
}

// setLineCount initializes an unordered_map, with two integer keys: 1 & 2 (for X and O respectively)
// ,and another unordered_map as value whose integer keys (for gridSize 3) represent rows, columns, and diagonals as:
// key 1,2,3 represents first, second, and third row
// key 4,5,6 represents first, second, and third column
// key 7, 8 represents left-right diagonal and right-left diagonal respecively
// and its values represent the count of 'X' or 'O' in that particular row, column, and diagonal

void Tictactoe::setLineCount(int grid_size) {
    for (int i = 1; i <=  grid_size+grid_size+2; i++) {
        lineCount[1][i] = 0;
        lineCount[2][i] = 0;
    }
}

void Tictactoe::displayGrid() {
    for(auto& i : grid) {
        for (auto& j : i) {
            std::cout << j << " " << '|' << " ";
        }
        std::cout << std::endl;
    }
}

void Tictactoe::setNumPlayers() {
    while(!(numPlayers == 1 || numPlayers == 2)) {
        std::cout << "Enter 1 for single player or 2 for double players: " << std::endl;
        if(!(std::cin >> numPlayers)) {
            std::cout << "Please enter numbers only: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n'); 
        }

    }
}

void Tictactoe::changeTurn() {
    turn = turn==1?2:1;
}

// checks rows, columns, and diagonals for all crosses or zeros and checks for draw
// For 'X', if lineCount key 1 (which is another unordered_map) has any key whose corresponding value is equal to 3
// then player 1 wins
// Similarly, for 'O', if lineCount key 2 (which is another unordered_map) has any key whose corresponding value is equal to 3
// then player 2 wins
int Tictactoe::isComplete() {
    for(auto x : lineCount) {
        for (auto y : x.second) {
            if (y.second == 3) {
                return 1;
            }
        }
    }
    if (filledCount == gridSize*gridSize) {
        return 2;
    }
    return 0;
}

// returns row and column for given move number (1-9 for gridSize == 3)
position Tictactoe::moveToPosition(int Move) {
    position pos;
    Move = Move-1;
    pos.row = Move/gridSize;
    pos.col = Move%gridSize;
    return pos;
}

// updates LineCount unordered_map whenever a move is played by any player
void Tictactoe::updateLineCount(int Turn, bool isIncreament, position pos) {
    if (isIncreament) {
        lineCount[Turn][pos.row+1]++;
        lineCount[Turn][gridSize+pos.col+1]++;
        
        if (pos.row == pos.col) {
            lineCount[Turn][gridSize+gridSize+1]++;
        }
        
        if (pos.row+pos.col == gridSize-1) {
            lineCount[Turn][gridSize+gridSize+2]++;
        }
    } else {
        lineCount[Turn][pos.row+1]--;
        lineCount[Turn][gridSize+pos.col+1]--;
        
        if (pos.row == pos.col) {
            lineCount[Turn][gridSize+gridSize+1]--;
        }
        
        if (pos.row+pos.col == gridSize-1) {
            lineCount[Turn][gridSize+gridSize+2]--;
        }
    }
}

// putMove function takes Turn (1 or 2 for 'X' and 'O' respectively) and Move (1-9 for gridSize == 3) as input
// and updates the grid
void Tictactoe::putMove(int Turn, int Move) {
    position pos = moveToPosition(Move);
    
    if (Turn == 1) {
        grid[pos.row][pos.col] = "X ";
    } else if (Turn == 2) {
        grid[pos.row][pos.col] = "O ";
    }

    updateLineCount(Turn, true, pos);

    filledCount++;
}

// removes (X / O) from grid and puts Move (1-9)
void Tictactoe::removeMove(int Move, int Turn) {
    position pos = moveToPosition(Move);
    
    if(Move < 10) {
        grid[pos.row][pos.col] = "0"+std::to_string(Move);
    } else {
        grid[pos.row][pos.col] = std::to_string(Move);
    }
    
    updateLineCount(Turn, false, pos);
    
    filledCount--;
}

void Tictactoe::getUserMove() {
    while(!isMoveValid()) {
        if (turn == 1) {
            std::cout << "Player 1: press number to place your move: " << std::endl;
            if(!(std::cin >> currentMove)) {
                std::cout << "Please enter numbers only: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n'); 
            }
        } else if(turn == 2) {
            std::cout << "Player 2: press number to place your move: " << std::endl;
            if(!(std::cin >> currentMove)) {
                std::cout << "Please enter numbers only: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n'); 
            }
        }
    }
}

// finds score for minimax
int Tictactoe::findScore(int Turn) {
    int gridStatus = isComplete();
    if(gridStatus == 1){
        if(Turn == 1) {
            return -10;
        } else if (Turn == 2) {
            return 10;
        }
    }
    if(gridStatus == 2) {
        return 1;
    }
    return 0; 
}

// checks if a particular position (row, col) in grid is filled 
bool Tictactoe::isFilled(int Move) {
    position pos = moveToPosition(Move);
    if (grid[pos.row][pos.col] == "X " || grid[pos.row][pos.col] == "O ") {
        return true;
    }
    return false;
}

// minimax function is called recursively to find optimal move
int Tictactoe::minimax(int Turn) {
    int score = findScore(Turn);
    int best = 0;
    if(score == 10 || score == -10) {
        return score;
    }
    if(score == 1) {
        return 0;
    }
    if(Turn == 1) {
        best = -1000000;
        for(int move = 1; move <= gridSize*gridSize; move++) {
            if(isFilled(move) == false) {
                putMove(Turn, move);
                best = std::max(best, minimax(Turn==1?2:1));
                removeMove(move, Turn);
            }
        }
    } else if (Turn == 2) {
        best = 1000000;
        for(int move = 1; move <= gridSize*gridSize; move++) {
            if(isFilled(move) == false) {
                putMove(Turn, move);
                best = std::min(best, minimax(Turn==1?2:1));
                removeMove(move, Turn);
            }
        }
    }
    return best;
}

// getOptimalMove takes turn (1/2 : X/O) and outputs optimal move (1 - 9 (for gridSize 3))
void Tictactoe::getOptimalMove(int Turn) {
    int bestScore = 0;
    int bestMove = 0;
    if(Turn == 1) {
        bestScore = -1000000;
    } else if (Turn == 2) {
        bestScore = 1000000;
    }
    for(int moveo = 1; moveo <= gridSize*gridSize; moveo++) { 
        if(isFilled(moveo) == false) {
            putMove(Turn, moveo);
            int moveScore = minimax(Turn==1?2:1);
            removeMove(moveo, Turn);
            if(Turn == 1) {
                if(moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = moveo;
                }
            } else if (Turn == 2) {
                if(moveScore < bestScore) {
                    bestScore = moveScore;
                    bestMove = moveo;
                }
            }
        }
    }
    currentMove = bestMove;
}

bool Tictactoe::isMoveValid() {
    if(currentMove > 0 && currentMove <= gridSize*gridSize && isFilled(currentMove) == false) { 
        return true;
    }
    return false;
}

std::string Tictactoe::play() {
    setNumPlayers();
    while(isComplete()==0) {
        if(turn==1) {
            displayGrid();
            std::cout << std::endl;
            getUserMove();
            putMove(turn, currentMove);
            std::cout << "Player 1 played at: " << currentMove << std::endl << std::endl;
            changeTurn();
        } else if (turn == 2){
            displayGrid();
            std::cout << std::endl;
            if(numPlayers == 1) {
                getOptimalMove(turn);
                putMove(turn, currentMove);
                std::cout << "Player 2 played at: " << currentMove << std::endl << std::endl;
                changeTurn();
            } else if(numPlayers == 2) {
                getUserMove();
                putMove(turn, currentMove);
                std::cout << "Player 2 played at: " << currentMove << std::endl << std::endl;
                changeTurn();
            }
        }
    }
    if(isComplete() == 1) {
        if(turn == 1) {
            displayGrid();
            return "Player 2 wins!!!";
        } else if (turn == 2) {
            displayGrid();
            return "Player 1 wins!!!";
        }
    }
    if (isComplete()==2) {
        displayGrid();
        return "Match Draw";
    }
    return "";
}