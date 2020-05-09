#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

//I am aware of the ease of using the "using std:: ...." lines. But while i'm still learning I prefer to write it
// all myself. To avoid silly mistakes like calling a vector vector.


//I added the last two enums which will represent the starting and ending position.
enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

//This array will be used to check the directions.
const int directions[4][2] {{0,1},{1,0},{-1,0}, {0,-1}};

//changing all the vectors to return States to make the grid more readable
std::vector<State> GridRow (std::string line) {
    std::vector<State> row;
    int n;
    char c;
    std::istringstream sline(line);
    while (sline >> n >> c && c == ',') {
        if (n == 0) {
        row.push_back(State::kEmpty);
    } else {
        row.push_back(State::kObstacle);
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

bool Compare (const std::vector<int> a, const std::vector<int> b){
    int f1 = a[2] + a[3];  //comparing the g value and the h value of two node vectors
    int f2 = b[2] + b[3]; 

    return f1 > f2;
}

//had heavy help with this function, note to self, research it
void CellSort (std::vector<std::vector<int>> *v){
    sort(v->begin(), v->end(), Compare);
}

//function to calculate the h value, the function works, but doesnt seem logical* note to self, ask sicco
int Heuristic (int x1, int x2, int y1, int y2){
    return std::abs(x2-x1)+ std::abs(y2-y1);
};

// checking if the cell is empty and and on the actual grid
bool CheckDaCells (int x, int y, std::vector<std::vector<State>> &grid) {
    bool xrow = (x >= 0 && x < grid.size());
    bool yrow = (y >= 0 && y < grid[0].size());
    if (xrow && yrow)
        return grid[x][y] == State::kEmpty;
     return false; 
}


//starting to work with references for this one
void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>>& dalist, std::vector<std::vector<State>>& grid){
    //instead of initializing a new vector to push into the 2d one, i just do it right away.
    dalist.push_back(std::vector<int>{x,y,g,h});
    grid[x][y] = State::kClosed;
}

void ExpandNeighbors (const std::vector<int> &currentnode, int finish[2], std::vector<std::vector<int>> &openlist, std::vector<std::vector<State>>& grid){
    //get current nodes data
    int x = currentnode[0];
    int y = currentnode[1];
    int g = currentnode[2];

    //Loop through the current node's current neighbors
    for (int i = 0; i<4; i++){
        int x2 = x + directions[i][0];
        int y2 = y + directions[i][1];

        if(CheckDaCells(x2,y2,grid)){
            int g2 = g+1;
            int h2 = Heuristic(x2, y2, finish[0], finish[1]);
            AddToOpen(x2,y2,g2,h2,openlist, grid);
        }
    }

}


// Time to begin the pathfinding function itself. done in parts
std::vector<std::vector<State>> Search (std::vector<std::vector<State>> grid, int start[2], int end[2]){

    std::vector<std::vector<int>> open;
 
    //here i will initialize the starting node.
    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = Heuristic(x,y, end[0], end[1]);

    // here i will add it to the the node to the open vector.
    AddToOpen(x, y, g, h, open, grid) ;

    while (open.size() > 0) {
        CellSort(&open);
        std::vector<int> currentnode = open.back();
        open.pop_back();

        x = currentnode[0];
        y = currentnode[1];
        grid[x][y] = State::kPath;

        if (x == end[0] && y == end[1]) {
            grid[start[0]][start[1]] = State::kStart;
            grid[end[0]][end[1]] = State::kFinish;
            return grid;
        }
        ExpandNeighbors(currentnode,end,open,grid);
    }
    std::cout<< "No path found!" << "\n";
    return std::vector<std::vector<State>>{};
}

//time to make enums to make our grid more readable.
std::string CellString (State cell){
    switch (cell){
        case State::kObstacle: return " (8)  ";
        case State::kPath: return "  §   ";
        case State::kStart: return "  !   ";
        case State::kFinish: return " =+=  ";
        default: return "  0   ";
      
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
    int start[2]{0,0};
    int end[2]{4,5};
    std::vector<std::vector<State>> board = ReadGrid("grid.txt");
    std::vector<std::vector<State>> solution = Search(board, start, end);
    PrintBoard(solution);
}