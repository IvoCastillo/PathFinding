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

//Making a function to read the grid and print it out.
void ReadGrid (std::string path){
    std::ifstream sgrid(path);
    std::string line;

    while (getline(sgrid,line)){
        std::cout<< line << "\n";
    }
}

//Now I want to not just show the info, but save it in a 2d vector to work with the data.
// So first I will make a function to get a row from the grid, and save it in a 1d vector.
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


int main() {   
    ReadGrid("grid.txt");
}