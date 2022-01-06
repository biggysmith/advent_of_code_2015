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

struct deer_t{
    std::string name;
    int velocity;
    int run_time;
    int rest_time;
    int pos = 0;
    int run_count = 0;
    int rest_count = 0;
    int score = 0;
    bool running = true;
};

using deers_t = std::vector<deer_t>;

auto load_input(const std::string& file){
    deers_t ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        deer_t deer;
        char str0[20];
        sscanf(line.c_str(), "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", str0, &deer.velocity, &deer.run_time, &deer.rest_time);
        deer.name = str0;
        deer.run_count = deer.run_time;
        deer.rest_count = deer.rest_time;
        ret.push_back(deer);
    }
    return ret;
}

auto part1(const deers_t& deers, int seconds)
{
    auto deers2 = deers;

    for(auto& deer : deers2){
        float run_rest_ratio = deer.run_time / (float)deer.rest_time;
        float sections = seconds / (float)(deer.rest_time + deer.run_time);
        float progress = sections - std::floor(sections);
        bool resting = progress > run_rest_ratio;
        deer.pos += deer.velocity * deer.run_time * (int)std::ceil(sections * (resting ? 1 : progress));
    }

    auto it = std::max_element(deers2.begin(), deers2.end(), [](auto& a,auto& b){
        return a.pos < b.pos;
    });
    return it->pos; 
}


auto part2(const deers_t& deers, int seconds)
{
    auto deers2 = deers;

    for(int i=0; i<seconds; ++i)
    {
        for(auto& deer : deers2)
        {
            if(deer.running){
                deer.pos += deer.velocity;
                deer.run_count--;
                if(deer.run_count == 0){
                    deer.running = false;
                    deer.rest_count = deer.rest_time;
                }
            }else{
                deer.rest_count--;
                if(deer.rest_count == 0){
                    deer.running = true;
                    deer.run_count = deer.run_time;
                }
            }
        }

        auto it = std::max_element(deers2.begin(), deers2.end(), [](auto& a,auto& b){
            return a.pos < b.pos;
        });

        for(auto& deer : deers2){
            if(deer.pos == it->pos){
                deer.score++;
            }
        }
    }

    auto it = std::max_element(deers2.begin(), deers2.end(), [](auto& a,auto& b){
        return a.score < b.score;
    });
    return it->score; 
}

void main()
{
    auto test_values = load_input("../src/day14/example_input.txt");
    auto actual_values = load_input("../src/day14/input.txt");

    std::cout << "part1: " << part1(test_values, 1000) << std::endl;
    std::cout << "part1: " << part1(actual_values, 2503) << std::endl;

    std::cout << "part2: " << part2(test_values, 1000) << std::endl;
    std::cout << "part2: " << part2(actual_values, 2503) << std::endl;
}
