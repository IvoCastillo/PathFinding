#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

enum class State {kEmpty, kObstacle};

//changing all the vectors to return States to make the grid more readable
std::vector<State> GridRow (std::string line) {
    std::vector<State> row;
    int n;
    char c;
    std::istringstream sline(line);
    while (sline >> n >> c && c == ',') {
        if (n == 1) {
        row.push_back(State::kObstacle);
    } else {
        row.push_back(State::kEmpty);
           }
    }
    return row;
}

std::vector<std::vector<State>> ReadGrid (std::string path){
    std::vector<std::vector<State>> board;
    std::ifstream sgrid(path);
    std::string line;

    while (getline(sgrid,line)){
        std::vector<State> row = GridRow(line);
        board.push_back(row);
    }
    return board;
}

// Time to begin the pathfinding function itself. done in parts
std::vector<std::vector<State>> Search (std::vector<std::vector<State>> grid, int start[2], int end[2]){
    std::vector<std::vector<State>> result;
    std::cout<< "No path found!" << "\n";
    return result;
}

//time to make enums to make our grid more readable.
std::string CellString (State cell){
    switch (cell){
        case State::kObstacle: return " (8)  ";
        case State::kEmpty: return "  0   ";
    }
}

void PrintBoard (const std::vector<std::vector<State>> grid){
    for (int i=0; i< grid.size(); i++) {
        for (int j=0; j < grid[i].size(); j++){
            std::cout << CellString (grid[i][j]);
        }
        std::cout << "\n";
    }
}

int main() {   
    std::vector<std::vector<State>> board = ReadGrid("grid.txt");
    int start[2]{0,0};
    int end[2] {4,5};
    std::vector<std::vector<State>> solution = Search(board, start, end);
    PrintBoard(solution);
}