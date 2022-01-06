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

struct edge_t{
    std::string from, to;
    int change;
};

using egdes_t = std::vector<edge_t>;

auto load_input(const std::string& file){
    egdes_t ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        edge_t edge;
        char str0[20];
        char str1[20];
        char str2[20];
        sscanf(line.c_str(), "%s would %s %d happiness units by sitting next to %s.", str0, str1, &edge.change, str2);
        edge.from = str0;
        edge.to = str2;
        if(strcmp(str1, "lose") == 0){
            edge.change *= -1;
        }
        if(edge.to.back() == '.'){
            edge.to.pop_back();
        }
        ret.push_back(edge);
    }
    return ret;
}

using graph_t = std::map<std::string,std::map<std::string,edge_t>>;

int mod(int a,int b){
    return (b + (a%b)) % b;
}

auto process(const egdes_t& edges, bool part2)
{
    std::set<std::string> dst;

    graph_t graph;
    for(auto& edge : edges){
        graph[edge.from][edge.to] = {edge.from,edge.to,edge.change};
        dst.insert(edge.from);
    }

    if(part2){
        for(auto& name : dst){
            graph[name]["biggy"] = {name,"biggy",0};
            graph["biggy"][name] = {"biggy",name,0};
        }
        dst.insert("biggy");
    }

    int max_dist = 0;
    std::vector<std::string> names(dst.begin(), dst.end());

    do {
        int local_sum = 0;
        for(int i=0; i<names.size(); ++i){
            local_sum += graph.at(names[i]).at(names[mod(i+1, (int)names.size())]).change;
            local_sum += graph.at(names[i]).at(names[mod(i-1, (int)names.size())]).change;
        }
        max_dist = std::max(max_dist, local_sum);
    } 
    while (std::next_permutation(names.begin(), names.end()));

    return max_dist;
}

void main()
{
    auto test_values = load_input("../src/day13/example_input.txt");
    auto actual_values = load_input("../src/day13/input.txt");

    std::cout << "part1: " << process(test_values, false) << std::endl;
    std::cout << "part1: " << process(actual_values, false) << std::endl;

    std::cout << "part2: " << process(actual_values, true) << std::endl;
}
