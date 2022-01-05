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

std::string load_input(const std::string& file){
    std::ifstream fs(file);
    std::string line;
    std::getline(fs, line);
    return line;
}

auto process(const std::string& in)
{
    int basement = INT_MAX;
    int pos = 0;
    for(int i=0; i<in.size(); ++i){
        pos += in[i] == '(' ? 1 : -1;
        if(basement==INT_MAX && pos == -1){
            basement = i+1;
        }
    }
    return std::make_pair(pos, basement);
}

void main()
{
    auto actual_values = load_input("../src/day01/input.txt");

    auto result = process(actual_values);

    std::cout << "part1: " << result.first << std::endl;
    std::cout << "part2: " << result.second << std::endl;
}
