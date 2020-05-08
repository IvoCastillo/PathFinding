#include <iostream>
#include <fstream>
#include <vector>


int main() {

    std::vector<int> gridRow {0,0,0,0,0,0,1};
    //making a txt file called grid where I will save the grid
    //manually added the rest of the grid out of laziness
    std::ofstream stream("grid.txt");

    //pushing the vector row into the txt file.

    for (auto v: gridRow) {
        stream << v << ',';
    }

//this code will all be deleted on the next commit except the grid.txt file
return 0;
}