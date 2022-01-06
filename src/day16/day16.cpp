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

struct sue_t{
    int num;
    std::map<std::string,int> things;
};

using sues_t = std::vector<sue_t>;

auto load_input(const std::string& file){
    sues_t ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        sue_t sue;
        char str0[20];
        char str1[20];
        char str2[20];
        int a,b,c;
        sscanf(line.c_str(), "Sue %d: %s %d, %s %d, %s %d", &sue.num, str0, &a, str1, &b, str2, &c);
        sue.things[str0] = a;
        sue.things[str1] = b;
        sue.things[str2] = c;
        ret.push_back(sue);
    }
    return ret;
}

auto process(const sues_t& in, bool part2)
{
    auto sues = in;

    std::map<std::string,int> our_sue = {
        { "children:", 3 },
        { "cats:", 7 },
        { "samoyeds:", 2 },
        { "pomeranians:", 3 },
        { "akitas:", 0 },
        { "vizslas:", 0 },
        { "goldfish:", 5 },
        { "trees:", 3 },
        { "cars:", 2 },
        { "perfumes:", 1 }
    };

    for(auto it=sues.begin(); it!=sues.end(); )
    {
        bool remove = false;
        for(auto& [thing,num] : it->things)
        {
            if(part2 && (thing == "cats:" || thing == "trees:")){
                if((our_sue[thing] >= num)){
                    remove = true;
                    break;
                }
            }else if(part2 && (thing == "pomeranians:" || thing == "goldfish:")){
                if((our_sue[thing] <= num)){
                    remove = true;
                    break;
                }
            }else if(our_sue[thing] != num){
                remove = true;
                break;
            }
        }

        if(remove){
            it = sues.erase(it);
            if(sues.size() == 1){
                return sues.front().num;
            }
        }else{
            it++;
        }
    }

    return -1;
}

void main()
{
    auto actual_values = load_input("../src/day16/input.txt");

    std::cout << "part1: " << process(actual_values, false) << std::endl;
    std::cout << "part2: " << process(actual_values, true) << std::endl;
}
