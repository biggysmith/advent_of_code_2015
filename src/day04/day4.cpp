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
#include <iterator>
#include <array>
#include "md5.h"

uint32_t md5_i(const std::string& s){
    md5_hash md5;
    md5.append((uint8_t*)s.data(),s.size());
    return md5.h0;
}

auto process(const std::string& in, uint32_t zeros)
{
    int pos = 0;
    while(true){
        uint32_t h = md5_i(in + std::to_string(pos));
        if((h & zeros) == 0){
            return pos;
        }
        pos++;
    }

    return 0;
}

void main()
{
    std::cout << "part1: " << process("iwrupvqb", 0x00F0FFFF) << std::endl;
    std::cout << "part2: " << process("iwrupvqb", 0x00FFFFFF) << std::endl;
}
