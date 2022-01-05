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

using strings_t = std::vector<std::string>;

auto load_input(const std::string& file){
    strings_t ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        ret.push_back(line);
    }
    return ret;
}

void replace_all(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

std::string hex_to_string(unsigned char c){
    std::stringstream ss;
    ss << "\\x" << std::setfill('0') << std::setw(2) << std::hex << +c;
    return ss.str();
}

auto part1(const strings_t& strings)
{
    size_t sum0 = 0;
    size_t sum1 = 0;
    for(auto& orig_string : strings)
    {
        std::string new_string = orig_string.substr(1, orig_string.size()-2);
        sum1 += orig_string.size();

        replace_all(new_string,  "\\\"", "\"");
        replace_all(new_string,  "\\\\", "\\");

        for(int c=0; c<256; ++c){
            replace_all(new_string, hex_to_string(c), std::string(1,c));
        }

        sum0 += new_string.size();
    }

    return sum1 - sum0;

}

auto part2(const strings_t& strings)
{
    size_t sum0 = 0;
    size_t sum1 = 0;
    for(auto& orig_string : strings)
    {
        std::stringstream ss;
        ss << std::quoted(orig_string);
        sum0 += orig_string.size();
        sum1 += ss.str().size();
    }
    return sum1 - sum0;
}

void main()
{
    auto test_values = load_input("../src/day08/example_input.txt");
    auto actual_values = load_input("../src/day08/input.txt");

    std::cout << "part1: " << part1(test_values) << std::endl;
    std::cout << "part1: " << part1(actual_values) << std::endl;
    std::cout << "part2: " << part2(test_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}
