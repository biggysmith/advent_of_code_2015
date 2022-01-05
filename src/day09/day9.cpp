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
#include <iomanip>

struct edge_t{
    std::string from, to;
    int dist;
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
        sscanf(line.c_str(), "%s to %s = %d", str0, str1, &edge.dist);
        edge.from = str0;
        edge.to = str1;
        ret.push_back(edge);
    }
    return ret;
}

using graph_t = std::map<std::string,std::vector<edge_t>>;

void min_max_dist(const graph_t& graph, const std::string& v, int current_dist, int& min_dist, int& max_dist, std::set<std::string>& path, const std::set<std::string>& dst)
{
    if(path == dst){
        min_dist = std::min(min_dist, current_dist);
        max_dist = std::max(max_dist, current_dist);
    }else{
        for(auto& edge : graph.at(v)){
            if(!path.count(edge.to)){
                path.insert(edge.to);
                min_max_dist(graph, edge.to, current_dist + edge.dist, min_dist, max_dist, path, dst);
                path.erase(edge.to);
            }
        }
    }
}

auto process(const egdes_t& edges)
{
    std::set<std::string> dst;

    graph_t graph;
    for(auto& edge : edges){
        graph[edge.from].push_back({edge.from,edge.to,edge.dist});
        graph[edge.to].push_back({edge.to,edge.from,edge.dist});
        dst.insert(edge.from);
        dst.insert(edge.to);
    }

    int min_dist = INT_MAX;
    int max_dist = 0;
    for(auto& src : dst){
        std::set<std::string> path{src};
        min_max_dist(graph, src, 0, min_dist, max_dist, path, dst);
    }
    return std::make_pair(min_dist, max_dist);

}

void main()
{
    auto test_values = load_input("../src/day09/example_input.txt");
    auto actual_values = load_input("../src/day09/input.txt");

    auto test_result = process(test_values);
    auto result = process(actual_values);

    std::cout << "part1: " << test_result.first << std::endl;
    std::cout << "part1: " << result.first << std::endl;
    std::cout << "part2: " << test_result.second << std::endl;
    std::cout << "part2: " << result.second << std::endl;
}
