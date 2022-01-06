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
#include "json11.hpp"

auto load_input(const std::string& file){
    std::string buf;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        buf += line + "\n";
    }
    std::string err;
    return json11::Json::parse(buf, err);
}

void search(const json11::Json& val, int& sum, bool part2)
{
    if(val.is_number()) {
        sum += (int)val.number_value();
    } 
    else if(val.is_object()) {
        if(part2){
            auto it = std::find_if(val.object_items().begin(), val.object_items().end(), [](auto& a){
                auto& [name,object] = a;
                return object.is_string() && object.string_value() == "red";
            });
            if(it != val.object_items().end()){
                return;
            }
        }

        for(auto& [name,object] : val.object_items()){
            search(object, sum, part2);
        }
    } 
    else if(val.is_array()) {
        for(auto& array : val.array_items()){
            search(array, sum, part2);
        }
    }
}


auto process(const json11::Json& tree, bool part2)
{
    int sum = 0;
    search(tree, sum, part2);
    return sum;
}

void main()
{
    auto actual_values = load_input("../src/day12/input.txt");

    std::cout << "part1: " << process(actual_values, false) << std::endl;
    std::cout << "part2: " << process(actual_values, true) << std::endl;
}
