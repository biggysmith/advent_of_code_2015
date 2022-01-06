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

using boxes_t = std::vector<int>;

auto load_input(const std::string& file){
    boxes_t ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        ret.push_back(std::stoi(line));
    }
    return ret;
}

template<typename F>
void power_set(const std::vector<int>& v, F&& f)
{
    int n = (int)v.size();
    int pn = 1 << n;

    for(int i=0; i<pn; ++i){
        std::vector<int> sub_set;
        for(int j=0; j<n; ++j){
            if(i & (1<<j)){
                sub_set.push_back(v[j]);
            }
        }
        f(sub_set);
    }
}

auto process(const boxes_t& in, int liters)
{
    int count = 0;
    int min_boxes_size = INT_MAX;
    int min_boxes_count = 0;

    power_set(in, [&](const boxes_t& boxes)
    {
        if(std::accumulate(boxes.begin(), boxes.end(), 0) == liters){
            if(boxes.size() < min_boxes_size){
                min_boxes_size = (int)boxes.size();
                min_boxes_count = 0;
            }
            if(boxes.size() == min_boxes_size){
                min_boxes_count++;
            }
            count++;
        }
    });

    return std::make_pair(count, min_boxes_count);
}

void main()
{
    auto test_values = load_input("../src/day17/example_input.txt");
    auto actual_values = load_input("../src/day17/input.txt");

    auto test_result = process(test_values, 25);
    auto result = process(actual_values, 150);

    std::cout << "part1: " << test_result.first << std::endl;
    std::cout << "part1: " << result.first << std::endl;

    std::cout << "part2: " << test_result.second << std::endl;
    std::cout << "part2: " << result.second << std::endl;
}
