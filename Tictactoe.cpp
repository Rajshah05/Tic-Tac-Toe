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