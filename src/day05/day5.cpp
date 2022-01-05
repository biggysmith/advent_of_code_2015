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
#include <regex>


std::vector<std::string> load_input(const std::string& file){
    std::vector<std::string> ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        ret.push_back(line);
    }
    return ret;
}

bool match_rule_0(const std::string& str){
    std::regex r("(\\w*[aeuio]\\w*){3,}");
    return std::regex_search(str, r);
}

bool match_rule_1(const std::string& str){
    std::regex r("(.)\\1");
    return std::regex_search(str, r);
}

bool match_rule_2(const std::string& str){
    std::regex r("^(?!.*(ab|cd|pq|xy)).*$");
    return std::regex_search(str, r);
}

bool part1_match(const std::string& str){
    return match_rule_0(str) && match_rule_1(str) && match_rule_2(str);
}

auto part1(const std::vector<std::string>& strs)
{
    return std::count_if(strs.begin(), strs.end(), part1_match);
}


bool match_rule_3(const std::string& str){
    std::regex r("(..).*\\1");
    return std::regex_search(str, r);
}

bool match_rule_4(const std::string& str){
    std::regex r("(.).\\1");
    return std::regex_search(str, r);
}

bool part2_match(const std::string& str){
    return match_rule_3(str) && match_rule_4(str);
}

auto part2(const std::vector<std::string>& strs)
{
    return std::count_if(strs.begin(), strs.end(), part2_match);
}

void main()
{
    auto actual_values = load_input("../src/day05/input.txt");

    std::cout << "part1: " << part1(actual_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}
