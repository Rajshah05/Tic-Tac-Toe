#include "Tictactoe.h"
#include <iostream>
#include <unordered_map>
#include <set>


Tictactoe::Tictactoe() {
    setGrid(3);
}

Tictactoe::Tictactoe(int grid_size) {
    setGrid(grid_size);
}

void Tictactoe::reset() {
    numPlayers = 0;
    turn = 1;
    currentMove = 0;
    filledCount = 0;
}

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
            lineCount1[n] = 0;
            lineCount2[n] = 0;
            n++;
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

int Tictactoe::isComplete() {
    for (auto x : lineCount1) {
        if (x.second == 3) {
            return 1;
        }
    }
    for (auto x : lineCount2) {
        if (x.second == 3) {
            return 1;
        }
    }
    if(filledCount == gridSize*gridSize) {
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
        std::cout << "Player 1 played at: " << currentMove << std::endl << std::endl;
        lineCount1[r+1]++;
        lineCount1[gridSize+c+1]++;
        if (r == c) {
            lineCount1[gridSize+gridSize+1]++;
        }
        if (r+c == gridSize-1) {
            lineCount1[gridSize+gridSize+2]++;
        }
    } else if (turn == 2) {
        grid[r][c] = "O ";
        std::cout << "Player 2 played at: " << currentMove << std::endl << std::endl;
        lineCount2[r+1]++;
        lineCount2[gridSize+c+1]++;
        if (r == c) {
            lineCount2[gridSize+gridSize+1]++;
        }
        if (r+c == gridSize-1) {
            lineCount2[gridSize+gridSize+2]++;
        }
    }

    filledCount++;
}

void Tictactoe::putMove(int tempTurn, int tempMove) {
    int x = tempMove-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if (tempTurn == 1) {
        grid[r][c] = "X ";
        lineCount1[r+1]++;
        lineCount1[gridSize+c+1]++;
        if (r == c) {
            lineCount1[gridSize+gridSize+1]++;
        }
        if (r+c == gridSize-1) {
            lineCount1[gridSize+gridSize+2]++;
        }
    } else if (tempTurn == 2) {
        grid[r][c] = "O ";
        lineCount2[r+1]++;
        lineCount2[gridSize+c+1]++;
        if (r == c) {
            lineCount2[gridSize+gridSize+1]++;
        }
        if (r+c == gridSize-1) {
            lineCount2[gridSize+gridSize+2]++;
        }
    }

    filledCount++;
}

void Tictactoe::removeMove(int tempMove, int tempTurn) {
    int x = tempMove-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if(tempMove < 10) {
        grid[r][c] = "0"+std::to_string(tempMove);
    } else {
        grid[r][c] = std::to_string(tempMove);
    }
    if (tempTurn == 1) {
        lineCount1[r+1]--;
        lineCount1[gridSize+c+1]--;
        if (r == c) {
            lineCount1[gridSize+gridSize+1]--;
        }
        if (r+c == gridSize-1) {
            lineCount1[gridSize+gridSize+2]--;
        }
    } else if (tempTurn == 2) {
        lineCount2[r+1]--;
        lineCount2[gridSize+c+1]--;
        if (r == c) {
            lineCount2[gridSize+gridSize+1]--;
        }
        if (r+c == gridSize-1) {
            lineCount2[gridSize+gridSize+2]--;
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

bool Tictactoe::isFilled(int Move) {
    int x = Move-1;
    int r = x/(gridSize);
    int c = (x%gridSize);
    if (grid[r][c] == "X " || grid[r][c] == "O ") {
        return true;
    }
    return false;
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
        for(int move1 = 1; move1 <= gridSize*gridSize; move1++) {
            if(isFilled(move1) == false) {
                putMove(tempTurn, move1);
                best = std::max(best, minimax(tempTurn==1?2:1));
                removeMove(move1, tempTurn);
            }
        }
    } else if (tempTurn == 2) {
        best = 1000000;
        for(int move2 = 1; move2 <= gridSize*gridSize; move2++) {
            if(isFilled(move2) == false) {
                putMove(tempTurn, move2);
                best = std::min(best, minimax(tempTurn==1?2:1));
                removeMove(move2, tempTurn);
            }
        }
    }
    return best;
}

void Tictactoe::getOptimalMove(int tempTurn) {
    int bestScore = 0;
    int bestMove = 0;
    if(tempTurn == 1) {
        bestScore = -1000000;
    } else if (tempTurn == 2) {
        bestScore = 1000000;
    }
    for(int moveo = 1; moveo <= gridSize*gridSize; moveo++) { 
        if(isFilled(moveo) == false) {
            putMove(tempTurn, moveo);
            int moveScore = minimax(tempTurn==1?2:1);
            removeMove(moveo, tempTurn);
            if(tempTurn == 1) {
                if(moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = moveo;
                }
            } else if (tempTurn == 2) {
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
        
}