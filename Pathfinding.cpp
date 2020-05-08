// to use cin & cout mostly as I understand it. 
#include <iostream>
/* to use ifstream & ofstream, we used ofstream to store a grid on another file. 
if the file does not exist it makes one.
we now use the ifstream to stream the file content, which we will use to make our grid.
*/
#include <fstream>
// pretty self-explanatory
#include <vector>
//we use sstream to split up the txt file.
#include <sstream>



//Now I want to not just show the info, but save it in a 2d vector to work with the data.
// This function is used to get a one line of strings, and split it into a number, the whole row will go into a 1d vector.
std::vector<int> GridRow (std::string line) {
    std::vector<int> row;
    int n;
    char c;
    std::istringstream sline(line);
    while (sline >> n >> c && c == ',') {
        row.push_back(n);
    }
    return row;
}

// now i'm changing this to return a 2d vector.
// Also I had to change the position of the functions. Since this function calls on GridRow,
// the function needs to be defined first to be able to get called upon.
std::vector<std::vector<int>> ReadGrid (std::string path){
    std::vector<std::vector<int>> board;
    std::ifstream sgrid(path);
    std::string line;

    while (getline(sgrid,line)){
        //making a 1d vector that will be take each string row, and push every vector row into the 2d vector.
        std::vector<int> row = GridRow(line);
        board.push_back(row);
    }
    return board;
}

int main() {   
    ReadGrid("grid.txt");
}