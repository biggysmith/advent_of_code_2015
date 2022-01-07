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

std::vector<int> load_input(const std::string& file){
    std::vector<int> ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        ret.push_back(std::stoi(line));
    }    
    return ret;
}

template<typename T,typename F>
void foreach_combination(const std::vector<T>& v,size_t count,F&& f)
{
    std::vector<uint8_t> bitset(count, 1);
    bitset.resize(v.size(), 0);
 
    std::vector<T> sub_set(count);

    do {
        int j = 0;
        for (std::size_t i = 0; i != v.size(); ++i) {
            if (bitset[i]) {
                sub_set[j++] = v[i];
            }
        }
        f(sub_set);
    } 
    while (std::prev_permutation(bitset.begin(),bitset.end()));
}

size_t sum(const std::vector<int>& v){
    return std::accumulate(v.begin(), v.end(), 0ull);
}

size_t quantum_entanglement(const std::vector<int>& v){
    return std::accumulate(v.begin(), v.end(), 1ull, std::multiplies<size_t>());
}

auto process(const std::vector<int>& packages,int ngroups)
{
    auto sum_total = sum(packages);
    auto sum_n = sum_total / ngroups;

    int set_size = 1;
    size_t min_qe = ULLONG_MAX;

    while(min_qe == ULLONG_MAX)
    {
        foreach_combination(packages, set_size, [&](auto& sub_set) 
        {    
            if(sum(sub_set) == sum_n){
                min_qe = std::min(min_qe, quantum_entanglement(sub_set));
            }
        });

        set_size++;
    }

    return min_qe;
}

void main()
{
    auto actual_values = load_input("../src/day24/input.txt");

    std::cout << "part1: " << process(actual_values, 3) << std::endl;
    std::cout << "part2: " << process(actual_values, 4) << std::endl;
}