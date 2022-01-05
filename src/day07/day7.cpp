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

struct instruction_t{
    std::string in0;
    std::string in1;
    std::string out;
    std::string op;
};

using instructions_t = std::map<std::string,instruction_t>;

instructions_t load_input(const std::string& file){
    instructions_t ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        instruction_t ins;
        char str0[20];
        char str1[20];
        char str2[20];
        char str3[20];
        auto nspaces = std::count(line.begin(),line.end(),' '); 
        if(nspaces == 2){
            sscanf(line.c_str(), "%s -> %s", str0, str1);
            ins.op = "SET";
            ins.in0 = str0;
            ins.out = str1;
        }else if(nspaces == 3){
            sscanf(line.c_str(), "%s %s -> %s", str0, str1, str2);
            ins.op = str0;
            ins.in0 = str1;
            ins.out = str2;
        }else if(nspaces == 4){
            sscanf(line.c_str(), "%s %s %s -> %s", str0, str1, str2, str3);
            ins.in0 = str0;
            ins.op = str1;
            ins.in1 = str2;
            ins.out = str3;
        }
        ret[ins.out] = ins;
    }
    return ret;
}

using wires_t = std::map<std::string,unsigned short>;

bool is_wire(const std::string& s){
    return s[0]>='a' && s[0]<='z';
}

unsigned short fetch(const instructions_t& ins, wires_t& wires, const std::string& wire)
{
    if(!is_wire(wire)){
        return std::stoi(wire);
    }

    if(wires.count(wire)){
        return wires[wire];
    }

    auto& in = ins.at(wire);

    if(in.op == "SET"){
        wires[in.out] = fetch(ins,wires,in.in0);
    }else if(in.op == "NOT"){
        wires[in.out] = ~fetch(ins,wires,in.in0);
    }else if(in.op == "AND"){
        wires[in.out] = fetch(ins,wires,in.in0) & fetch(ins,wires,in.in1);
    }else if(in.op == "OR"){
        wires[in.out] = fetch(ins,wires,in.in0) | fetch(ins,wires,in.in1);
    }else if(in.op == "LSHIFT"){
        wires[in.out] = fetch(ins,wires,in.in0) << fetch(ins,wires,in.in1);
    }else if(in.op == "RSHIFT"){
        wires[in.out] = fetch(ins,wires,in.in0) >> fetch(ins,wires,in.in1);
    }else{
        throw std::exception("unrecognized op");
    }

    return wires[in.out];
}

auto part1(const instructions_t& instructions)
{
    wires_t wires;
    return fetch(instructions, wires, "a");
}

auto part2(const instructions_t& instructions)
{
    wires_t wires;
    auto a = fetch(instructions, wires, "a");

    wires = {{"b", a}};
    return fetch(instructions, wires, "a");
}

void main()
{
    auto test_values = load_input("../src/day07/example_input.txt");
    auto actual_values = load_input("../src/day07/input.txt");

    std::cout << "part1: " << part1(actual_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}
