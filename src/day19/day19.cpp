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
#include <random>

using map_t = std::multimap<std::string,std::string>;

struct replacements_t{
    map_t rules;
    std::string molecule;
};

auto load_input(const std::string& file){
    replacements_t ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        if(line == ""){
            std::getline(fs, line);
            ret.molecule = line;
            break;
        }
        char str0[128];
        char str1[128];
        sscanf(line.c_str(), "%s => %s", str0, str1);
        ret.rules.insert({str0,str1});
    }
    return ret;
}

auto part1(const replacements_t& in)
{
    std::set<std::string> new_molecules;

    for(auto& [from,to] : in.rules)
    {       
        size_t start_pos = 0;
        while((start_pos = in.molecule.find(from, start_pos)) != std::string::npos) {
            std::string new_str = in.molecule;
            new_str.replace(start_pos, from.length(), to);
            new_molecules.insert(new_str);
            start_pos += from.length();
        }
    }

    return new_molecules.size();
}

auto part2(const replacements_t& in)
{
    std::vector<std::pair<std::string,std::string>> reverse;
    for (auto& [from,to] : in.rules){
        reverse.push_back({to,from});
    }

    auto rng = std::default_random_engine{};

    while(true)
    {        
        std::string molecule = in.molecule;

        int count = 0;
        int steps = 0;
        std::shuffle(reverse.begin(), reverse.end(), rng);

        while(true)
        {
            for (auto& [to,from] : reverse)
            {
                size_t pos = molecule.find(to, 0);
                if (pos != std::string::npos)
                {
                    steps++;
                    molecule.replace(pos, to.length(), from);
                    if(molecule == "e"){
                        return steps;
                    }

                }
                count++;
            }

            if(count > 1000){ // we are stuck, try another random config
                break;
            }
        }
    }

    return -1;
}

void main()
{
    auto actual_values = load_input("../src/day19/input.txt");

    std::cout << "part1: " << part1(actual_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}
