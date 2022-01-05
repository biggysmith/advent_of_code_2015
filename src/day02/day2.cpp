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

struct box_t{
    size_t l,w,h;
};

std::vector<box_t> load_input(const std::string& file){
    std::vector<box_t> ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        box_t box;
        sscanf(line.c_str(), "%zux%zux%zu", &box.l, &box.w, &box.h);
        ret.push_back(box);
    }
    return ret;
}

size_t area(const box_t& box){
    size_t a = box.l * box.w;
    size_t b = box.w * box.h;
    size_t c = box.h * box.l;
    return 2*(a + b + c) + std::min(a, std::min(b, c));
}

size_t ribbon(const box_t& box){
    return box.l * box.w * box.h + 2*std::min(box.l+box.w, std::min(box.w+box.h, box.h+box.l));
}

auto process(const std::vector<box_t>& boxes)
{
    size_t paper = std::accumulate(boxes.begin(), boxes.end(), 0ull, [](auto& a,auto& b){
        return a + area(b);
    });

    size_t ribbons = std::accumulate(boxes.begin(), boxes.end(), 0ull, [](auto& a,auto& b){
        return a + ribbon(b);
    });

    return std::make_pair(paper, ribbons);
}

void main()
{
    auto actual_values = load_input("../src/day02/input.txt");

    auto result = process(actual_values);

    std::cout << "part1: " << result.first << std::endl;
    std::cout << "part2: " << result.second << std::endl;
}
