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

bool match_rule_0(const std::string& str){
    for(int i=0; i<str.size()-2; ++i){
        if(str[i]+1 == str[i+1] && str[i+1]+1 == str[i+2]){
            return true;
        }
    }
    return false;
}

bool match_rule_1(const std::string& str){
    for(int i=0; i<str.size(); ++i){
        if(str[i] == 'i' || str[i] == 'o' || str[i] == 'l'){
            return false;
        }
    }
    return true;
}

bool match_rule_2(const std::string& str){
    char repeat = ' ';
    int count = 0;
    for(int i=0; i<str.size()-1; ++i){
        if(repeat != str[i] && str[i] == str[i+1]){
            repeat = str[i];
            count++;
            i++;
        }
        if(count > 1){
            return true;
        }
    }
    return false;
}

bool match(const std::string& password){
    return match_rule_0(password) && match_rule_1(password) && match_rule_2(password);
}

void increment(std::string& n)
{
    // work of art...
    auto pos = n.size()-1;
    n[pos]++;    
    if(n[pos] > 'z'){
        n[pos] = 'a';
        n[pos-1]++;
        if(n[pos-1] > 'z'){
            n[pos-1] = 'a';
            n[pos-2]++;
            if(n[pos-2] > 'z'){
                n[pos-2] = 'a';
                n[pos-3]++;
                if(n[pos-3] > 'z'){
                    n[pos-3] = 'a';
                    n[pos-4]++;
                    if(n[pos-4] > 'z'){
                        n[pos-4] = 'a';
                        n[pos-5]++;
                        if(n[pos-5] > 'z'){
                            n[pos-5] = 'a';
                            n[pos-6]++;
                            if(n[pos-6] > 'z'){
                                n[pos-6] = 'a';
                                n[pos-7]++;
                            }
                        }
                    }
                }
            }
        }          
    }
}

std::string find_next_password(std::string password)
{
    while(true){
        increment(password);
        if(match(password)){
            return password;
        }
    }
    return "";
}

void main()
{
    auto next = find_next_password("hxbxwxba");
    std::cout << "part1: " << next << std::endl;
    std::cout << "part2: " << find_next_password(next) << std::endl;
}
