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

auto look_and_say(const std::string& input)
{
    std::string ret;

    int last = input[0];
    int count = 0;
    for(int i=0; i<=input.size(); ++i){
        if(i<input.size() && last == input[i]){
            count++;
        }else{
            ret += count+'0';
            ret += last;
            count = 1;
            last = input[i];
        }
    }

    return ret;
}

auto part1(const std::string& input, int steps)
{
    auto ret = input;
    for(int i=0; i<steps; ++i){
        ret = look_and_say(ret);
    }
    return ret.size();
}

void main()
{
    std::cout << "part1:" << part1("3113322113", 40) << std::endl;
    std::cout << "part2:" << part1("3113322113", 50) << std::endl;
}
