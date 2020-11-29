#include "Tictactoe.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <set>


Tictactoe::Tictactoe() {
    setGrid(3);
}

void Tictactoe::setGrid(int grid_size) {
    auto n = 1;
    gridSize = grid_size;
    grid = std::vector<std::vector<std::string>> (gridSize, std::vector<std::string>(gridSize));
    filled = std::vector<bool> (gridSize*gridSize);
    for(auto& i : grid) {
        for(auto& j : i) {
            if(n < 10) {
                j = "0"+std::to_string(n);
            } else {
                j = std::to_string(n);
            }
            n++;
            filled[n-1] = false;
        }
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
        std::cin >> numPlayers;
    }
}

bool Tictactoe::checkCrossed(std::set<std::string> line) {
    if(line.size() == 1 && (line.count("X ") == 1 || line.count("O ")==1)) {
        return true;
    }
    return false;
}


int Tictactoe::isComplete() {
    std::unordered_map<int,std::set<std::string>> row_set;
    std::unordered_map<int,std::set<std::string>> col_set;
    std::set<std::string> leftRightDiagonal;
    std::set<std::string> rightLeftDiagonal;
    int filledCount = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            row_set[i].insert(grid[i][j]);
            col_set[j].insert(grid[i][j]);
            if(i==j) {
                leftRightDiagonal.insert(grid[i][j]);
            }
            if (i+j == gridSize-1) {
                rightLeftDiagonal.insert(grid[i][j]);
            }
            if (grid[i][j] == "X " || grid[i][j] == "O ") {
                filledCount++;
            }
        }
        if(checkCrossed(row_set[i])) {
            return 1;
        }
    }
    for (int i = 0; i < gridSize; i++) {
        if(checkCrossed(col_set[i])) {
            return 1;
        }
    }
    if(checkCrossed(leftRightDiagonal) || checkCrossed(rightLeftDiagonal)) {
        return 1;
    }


    if (filledCount == gridSize*gridSize) {
        return 2;
    }
    return 0;
}

void Tictactoe::putMove() {
    int x = currentMove-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if (turn == 1) {
        grid[r][c] = "X ";
    } else if (turn == 2) {
        grid[r][c] = "O ";
    }
    filled[x] = true;
}

void Tictactoe::putMove(int tempTurn, int tempMove) {
    int x = tempMove-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if (tempTurn == 1) {
        grid[r][c] = "X ";
    } else if (tempTurn == 2) {
        grid[r][c] = "O ";
    }
    filled[x] = true;
}

void Tictactoe::removeMove(int tempMove) {
    int x = tempMove-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if(tempMove < 10) {
        grid[r][c] = "0"+std::to_string(tempMove);
    } else {
        grid[r][c] = std::to_string(tempMove);
    }
    filled[x] = false;
}

int Tictactoe::findScore(int tempTurn) {
    int gridStatus = isComplete();
    if(gridStatus == 1){
        if(tempTurn == 1) {
            return -10;
        } else if (tempTurn == 2) {
            return 10;
        }
    }
    if(gridStatus == 2) {
        return 1;
    }
    return 0; 
}


int Tictactoe::minimax(int tempTurn) {
    int score = findScore(tempTurn);
    int best = 0;
    if(score == 10 || score == -10) {
        return score;
    }
    if(score == 1) {
        return 0;
    }
    if(tempTurn == 1) {
        best = -1000000;
        for(int i = 1; i <= gridSize*gridSize; i++) {
            if(filled[i-1] == false) {
                // currentMove = i;
                putMove(tempTurn, i);
                best = std::max(best, minimax(tempTurn==1?2:1));
                removeMove(i);
            }
        }
    } else if (tempTurn == 2) {
        best = 1000000;
        for(int i = 1; i <= gridSize*gridSize; i++) {
            if(filled[i-1] == false) {
                // currentMove = i;
                putMove(tempTurn, i);
                best = std::min(best, minimax(tempTurn==1?2:1));
                removeMove(i);
            }
        }
    }
    return best;
}

int Tictactoe::optimalComputerMove(int tempTurn) {
    int bestScore = 0;
    int bestMove = 0;
    if(tempTurn == 1) {
        bestScore = -1000000;
    } else if (tempTurn == 2) {
        bestScore = 1000000;
    }
    for(int i = 1; i <= gridSize*gridSize; i++) {
        if(filled[i-1] == false) {
            // int tempMove = i;  
            putMove(tempTurn, i);
            int moveScore = minimax(tempTurn==1?2:1);
            // displayGrid();
            // std::cout << std::endl << std::endl;
            removeMove(i);
            if(tempTurn == 1) {
                if(moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = i;
                }
            } else if (tempTurn == 2) {
                if(moveScore < bestScore) {
                    bestScore = moveScore;
                    bestMove = i;
                }
            }
        }
    }
    return bestMove;
}

bool Tictactoe::isMoveValid() {
    if(currentMove > 0 && currentMove <= gridSize*gridSize && filled[currentMove-1] == false) { 
        return true;
    }
    return false;
}

int Tictactoe::play() {
    setNumPlayers();
    while(isComplete()==0) {
        if(turn==1) {
            displayGrid();
            std::cout << std::endl;
            while(!isMoveValid()) {
                std::cout << "Player 1: press number to place your move: " << std::endl;
                std::cin >> currentMove;
            }
            putMove();
            turn = 2;
        } else if (turn == 2){
            displayGrid();
            std::cout << std::endl;
            if(numPlayers == 1) {
                currentMove = optimalComputerMove(turn);
                std::cout << "Computer played at: " << currentMove << std::endl << std::endl;
                putMove();
                turn = 1;
            } else if(numPlayers == 2) {
                while(!isMoveValid()) {
                    std::cout << "Player 2: press number to place your move: " << std::endl;
                    std::cin >> currentMove;
                }
                putMove();
                turn = 1;
            }
        }
    }
    if(isComplete() == 1) {
        if(turn == 1) {
            displayGrid();
            std::cout << "Player 2 wins!!!" << std::endl;
        } else if (turn == 2) {
            displayGrid();
            std::cout << "Player 1 wins!!!" << std::endl;
        }
    }
    if (isComplete()==2) {
        displayGrid();
        std::cout << "Match Draw" << std::endl;
    }
        
}