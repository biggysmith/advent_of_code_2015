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

int divisors_sum(int n)
{
    int sum = 0;
    for (int i=1; i<=sqrt(n); ++i)
    {
        if(n % i == 0){
            sum += i;
            int d = n/i;
            if(d!=i){
                sum += d;
            }
        }
    }
    return sum;
}

auto part1(int input)
{
    int i = 1;
    while(true){
        int presents = 10 * divisors_sum(i);
        if(presents >= input){
            break;
        }
        i++;
    }
    return i; 
}

int divisors_sum2(int n)
{
    int sum = 0;
    for (int i=1; i<=sqrt(n); ++i)
    {
        if(n % i == 0){
            int d = n/i;
            if(d <= 50){
                sum += i;
            }
            if(d!=i && i <= 50){ // to the FIRST 50 houses.... stupid wording of question
                sum += d;
            }
        }
    }
    return sum;
}

auto part2(int input)
{
    int i = 1;
    while(true){
        int presents = 11 * divisors_sum2(i);
        if(presents >= input){
            break;
        }        
        i++;
    }
    return i; 
}

void main()
{
    std::cout << "part1: " << part1(29000000) << std::endl;
    std::cout << "part2: " << part2(29000000) << std::endl;
}
