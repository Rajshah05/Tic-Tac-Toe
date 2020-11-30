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

// resets the data members to initial condition
void Tictactoe::reset() {
    numPlayers = 0;
    turn = 1;
    currentMove = 0;
    filledCount = 0;
    setLineCount(gridSize);
}

// creates a grid (board)
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

// 4-5 lines
void Tictactoe::setLineCount(int grid_size) {
    for (int i = 1; i <=  grid_size+grid_size+2; i++) {
        lineCountX[i] = 0;
        lineCountO[i] = 0;
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
int Tictactoe::isComplete() {
    for (auto x : lineCountX) {
        if (x.second == 3) {
            return 1;
        }
    }
    for (auto x : lineCountO) {
        if (x.second == 3) {
            return 1;
        }
    }
    if(filledCount == gridSize*gridSize) {
        return 2;
    }
    return 0;
}

// put move (X / O) in grid
void Tictactoe::putMove() {
    int x = currentMove-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if (turn == 1) {
        grid[r][c] = "X ";
        std::cout << "Player 1 played at: " << currentMove << std::endl << std::endl;
        
        lineCountX[r+1]++;
        lineCountX[gridSize+c+1]++;
        
        if (r == c) {
            lineCountX[gridSize+gridSize+1]++;
        }
        
        if (r+c == gridSize-1) {
            lineCountX[gridSize+gridSize+2]++;
        }
    } else if (turn == 2) {
        grid[r][c] = "O ";
        std::cout << "Player 2 played at: " << currentMove << std::endl << std::endl;
        
        lineCountO[r+1]++;
        lineCountO[gridSize+c+1]++;
        
        if (r == c) {
            lineCountO[gridSize+gridSize+1]++;
        }
        
        if (r+c == gridSize-1) {
            lineCountO[gridSize+gridSize+2]++;
        }
    }

    filledCount++;
}

void Tictactoe::putMove(int Turn, int Move) {
    int x = Move-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if (Turn == 1) {
        grid[r][c] = "X ";
        lineCountX[r+1]++;
        lineCountX[gridSize+c+1]++;
        if (r == c) {
            lineCountX[gridSize+gridSize+1]++;
        }
        if (r+c == gridSize-1) {
            lineCountX[gridSize+gridSize+2]++;
        }
    } else if (Turn == 2) {
        grid[r][c] = "O ";
        lineCountO[r+1]++;
        lineCountO[gridSize+c+1]++;
        if (r == c) {
            lineCountO[gridSize+gridSize+1]++;
        }
        if (r+c == gridSize-1) {
            lineCountO[gridSize+gridSize+2]++;
        }
    }

    filledCount++;
}

// removes move (X / O) from grid
void Tictactoe::removeMove(int Move, int Turn) {
    int x = Move-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if(Move < 10) {
        grid[r][c] = "0"+std::to_string(Move);
    } else {
        grid[r][c] = std::to_string(Move);
    }
    if (Turn == 1) {
        lineCountX[r+1]--;
        lineCountX[gridSize+c+1]--;
        if (r == c) {
            lineCountX[gridSize+gridSize+1]--;
        }
        if (r+c == gridSize-1) {
            lineCountX[gridSize+gridSize+2]--;
        }
    } else if (Turn == 2) {
        lineCountO[r+1]--;
        lineCountO[gridSize+c+1]--;
        if (r == c) {
            lineCountO[gridSize+gridSize+1]--;
        }
        if (r+c == gridSize-1) {
            lineCountO[gridSize+gridSize+2]--;
        }
    }
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

// checks if a particular position in grid is filled 
bool Tictactoe::isFilled(int Move) {
    int x = Move-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if (grid[r][c] == "X " || grid[r][c] == "O ") {
        return true;
    }
    return false;
}

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
            putMove();
            changeTurn();
        } else if (turn == 2){
            displayGrid();
            std::cout << std::endl;
            if(numPlayers == 1) {
                getOptimalMove(turn);
                putMove();
                changeTurn();
            } else if(numPlayers == 2) {
                getUserMove();
                putMove();
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