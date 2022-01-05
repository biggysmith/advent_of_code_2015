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

struct pos_t{
    int x,y;
};

struct instruction_t{
    std::string op;
    pos_t start, end;
};

struct grid_t{
    grid_t(int w,int h) : width(w), height(h), points(w*h, 0) {}

    int& get(int x,int y) { return points[y*width+x]; }
    const int& get(int x,int y) const { return points[y*width+x]; }

    void toggle(const pos_t& s,const pos_t& e, bool part1){
        for(int y=s.y; y<=e.y; ++y){
            for(int x=s.x; x<=e.x; ++x){
                if(part1){
                    get(x,y) = !get(x,y);
                }else{
                    get(x,y) += 2;
                }
            }
        }
    }

    void turn(const pos_t& s,const pos_t& e, bool onoff, bool part1){
        for(int y=s.y; y<=e.y; ++y){
            for(int x=s.x; x<=e.x; ++x){
                if(part1){
                    get(x,y) = onoff;
                }else{
                    get(x,y) = std::max(get(x,y) + (onoff ? 1 : -1), 0);
                }
            }
        }
    }

    std::vector<int> points;
    int width, height;
};

std::vector<instruction_t> load_input(const std::string& file){
    std::vector<instruction_t> ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        instruction_t ins;
        if(line.find("turn on") != std::string::npos){
            ins.op = "turn on";
            sscanf(line.c_str(), "turn on %d,%d through %d,%d", &ins.start.x, &ins.start.y, &ins.end.x, &ins.end.y);
        }else if(line.find("turn off") != std::string::npos){
            ins.op = "turn off";
            sscanf(line.c_str(), "turn off %d,%d through %d,%d", &ins.start.x, &ins.start.y, &ins.end.x, &ins.end.y);
        }else if(line.find("toggle") != std::string::npos){
            ins.op = "toggle";
            sscanf(line.c_str(), "toggle %d,%d through %d,%d", &ins.start.x, &ins.start.y, &ins.end.x, &ins.end.y);
        }
        ret.push_back(ins);
    }
    return ret;
}

auto process(const std::vector<instruction_t>& instructions, bool part1)
{
    grid_t grid(1000, 1000);

    for(auto& ins : instructions){
        if(ins.op == "turn on"){
            grid.turn(ins.start, ins.end, true, part1);
        }else if(ins.op == "turn off"){
            grid.turn(ins.start, ins.end, false, part1);
        }else if(ins.op == "toggle"){
            grid.toggle(ins.start, ins.end, part1);
        }
    }

    return std::accumulate(grid.points.begin(), grid.points.end(), 0);
}

void main()
{
    auto actual_values = load_input("../src/day06/input.txt");

    std::cout << "part1: " << process(actual_values, true) << std::endl;
    std::cout << "part2: " << process(actual_values, false) << std::endl;
}
