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
    std::string op;
    std::string x;
    std::string y;
};

std::vector<instruction_t> load_input(const std::string& file){
    std::vector<instruction_t> ret;
    std::ifstream fs(file);
    std::string line;
    std::string dummy;
    while(std::getline(fs, line)){
        std::stringstream ss(line);
        instruction_t ins;
        ss >> ins.op >> ins.x >> ins.y;
        if(ins.x.back() == ','){
            ins.x.pop_back();
        }
        ret.push_back(ins);
    }    
    return ret;
}

struct program_t
{
    program_t(const std::vector<instruction_t>& in) : instructions(in) {}

    void run()
    {
        auto get = [&](const std::string& s){
            return (s[0]>='a' && s[0]<='z') ? regs[s] : std::stoll(s);
        };

        while(ipos < instructions.size())
        {
            auto& ins = instructions[ipos];

            if(ins.op == "hlf"){
                regs[ins.x] /= 2;
            }else if(ins.op == "tpl"){
                regs[ins.x] *= 3;
            }else if(ins.op == "inc"){
                regs[ins.x]++;
            }else if(ins.op == "jmp"){
                ipos += get(ins.x) - 1;
            }else if(ins.op == "jie"){
                if(get(ins.x) % 2 == 0){
                    ipos += get(ins.y) - 1;
                }
            }else if(ins.op == "jio"){
                if(get(ins.x) == 1){
                    ipos += get(ins.y) - 1;
                }
            }else{
                break;
            }

            ipos++;
        }
    }

    int64_t b_value() const{
        return regs.at("b");
    }

    std::vector<instruction_t> instructions;
    std::map<std::string,int64_t> regs;
    size_t ipos = 0;
};

auto part1(const std::vector<instruction_t>& in)
{
    program_t prog(in);
    prog.run();
    return prog.b_value();
}


auto part2(const std::vector<instruction_t>& in)
{
    program_t prog(in);
    prog.regs["a"] = 1;
    prog.run();
    return prog.b_value();
}

void main()
{
    auto actual_values = load_input("../src/day23/input.txt");

    std::cout << "part1: " << part1(actual_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}