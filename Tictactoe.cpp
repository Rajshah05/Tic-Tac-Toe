#include "Tictactoe.h"
#include <iostream>
#include <string>


using namespace std;

Tictactoe::Tictactoe() {
    setGrid(3);
}

void Tictactoe::setGrid(int grid_size) {
    auto n = 1;
    gridSize = grid_size;
    grid = vector<vector<string>> (gridSize, vector<string>(gridSize));
    filled = vector<bool> (gridSize*gridSize);
    for(auto& i : grid) {
        for(auto& j : i) {
            if(n < 10) {
                j = "0"+to_string(n);
            } else {
                j = to_string(n);
            }
            n++;
            filled[n-1] = false;
        }
    }
}

void Tictactoe::displayGrid() {
    for(auto& i : grid) {
        for (auto& j : i) {
            cout << j << " " << '|' << " ";
        }
        cout << endl;
    }
}