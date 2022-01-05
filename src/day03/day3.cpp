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
#include <iterator>

struct pos_t{
    int x,y;
};

bool operator<(const pos_t& a,const pos_t& b){
    return std::make_tuple(a.x,a.y) < std::make_tuple(b.x,b.y);
}

std::string load_input(const std::string& file){
    std::ifstream fs(file);
    std::string line;
    std::getline(fs, line);
    return line;
}

auto part1(const std::string& directions)
{
    pos_t pos = {0,0};
    std::set<pos_t> houses;
    for(auto& dir : directions){
        if(dir == '>'){
            pos.x++;
        }else if(dir == 'v'){
            pos.y++;
        }else if(dir == '<'){
            pos.x--;
        }else if(dir == '^'){
            pos.y--;
        }
        houses.insert(pos);
    }

    return houses.size();
}

auto part2(const std::string& directions)
{
    pos_t santa_pos = {0,0};
    pos_t robo_santa_pos = {0,0};
    std::set<pos_t> santa_houses;
    std::set<pos_t> robo_santa_houses;
    santa_houses.insert({0,0});
    robo_santa_houses.insert({0,0});
    for(int i=0; i<directions.size(); ++i){
        auto dir = directions[i];
        auto& pos = i%2 == 0 ? santa_pos : robo_santa_pos;
        auto& houses = i%2 == 0 ? santa_houses : robo_santa_houses;
        if(dir == '>'){
            pos.x++;
        }else if(dir == 'v'){
            pos.y++;
        }else if(dir == '<'){
            pos.x--;
        }else if(dir == '^'){
            pos.y--;
        }
        houses.insert(pos);
    }

    std::set<pos_t> inter;
    std::set_union(santa_houses.begin(), santa_houses.end(), robo_santa_houses.begin(), robo_santa_houses.end(), std::inserter(inter, inter.end()));

    return inter.size();
}

void main()
{
    auto actual_values = load_input("../src/day03/input.txt");

    std::cout << "part1: " << part1(actual_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}
