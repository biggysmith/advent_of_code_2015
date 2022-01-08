#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <set>
#include <map>
#include <queue>

struct pos_t{
    int col,row;
};

pos_t load_input(const std::string& file){
    pos_t ret;
    std::ifstream fs(file);
    std::string line;
    std::getline(fs, line);
    sscanf(line.c_str(), "To continue, please consult the code grid in the manual.  Enter the code at row %d, column %d.", &ret.row, &ret.col);
    return ret;
}

auto process(const pos_t& pos)
{
    size_t next = 20151125;

    int ymax = 2;
    pos_t ipos {1,2};

    while(true)
    {
        next = (next * 252533) % 33554393;

        if(ipos.row == pos.row && ipos.col == pos.col){
            break;
        }

        ipos.col++;
        ipos.row--;

        if(ipos.row == 0){
            ymax++;
            ipos.row = ymax;
            ipos.col = 1;
        }
    }

    return next; 
}

void main()
{
    auto actual_values = load_input("../src/day25/input.txt");

    std::cout << "part1: " << process(actual_values) << std::endl;
}