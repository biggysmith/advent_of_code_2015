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

struct grid_t{
    char& get(int x,int y) { return points[y*width+x]; }
    const char& get(int x,int y) const { return points[y*width+x]; }

    bool corner(int x,int y) const { 
        return (x==0 && y==0) || (x==width-1 && y==0) || (x==width-1 && y==height-1) || (x==0 && y==height-1); 
    };

    bool on(int x,int y,bool part2) const { 
        if(part2 && corner(x,y)){
            return true;
        }
        return (x>=0 && y>=0 && x<width && y<height) ? get(x,y)=='#' : false; 
    }

    std::vector<char> points;
    int width, height;
};

auto load_input(const std::string& file){
    grid_t ret;
    std::ifstream fs(file);
    std::string line;
    ret.width = ret.height = 0;
    while(std::getline(fs, line)){
        ret.points.insert(ret.points.end(), line.begin(), line.end());
        ret.height++;
        ret.width = std::max(ret.width, (int)line.size());
    }
    return ret;
}

auto process(const grid_t& in, int steps, bool part2)
{
    auto grid0 = in;

    if(part2){
        grid0.get(0,0) = '#';
        grid0.get(grid0.width-1,0) = '#';
        grid0.get(0,grid0.height-1) = '#';
        grid0.get(grid0.width-1,grid0.height-1) = '#';
    }

    auto grid1 = grid0;

    for(int i=0; i<steps; ++i)
    {
        for(int y=0; y<grid0.height; ++y){
            for(int x=0; x<grid0.width; ++x){

                if(part2 && grid0.corner(x,y)){
                    continue;
                }
    
                int on_count = 0;
                on_count += grid0.on(x-1,y-1,part2);
                on_count += grid0.on(x+0,y-1,part2);
                on_count += grid0.on(x+1,y-1,part2);
                on_count += grid0.on(x-1,y+0,part2);
                on_count += grid0.on(x+1,y+0,part2);
                on_count += grid0.on(x-1,y+1,part2);
                on_count += grid0.on(x+0,y+1,part2);
                on_count += grid0.on(x+1,y+1,part2);

                if(grid0.on(x,y,part2) && !(on_count==2 || on_count==3)){
                    grid1.get(x,y) = '.';
                }
                else if(on_count==3){
                    grid1.get(x,y) = '#';
                }
            
            }
        }

        grid0 = grid1;
    }

    return std::count(grid0.points.begin(), grid0.points.end(), '#');
}

void main()
{
    auto test_values = load_input("../src/day18/example_input.txt");
    auto actual_values = load_input("../src/day18/input.txt");

    std::cout << "part1: " << process(test_values, 4, false) << std::endl;
    std::cout << "part1: " << process(actual_values, 100, false) << std::endl;

    std::cout << "part2: " << process(test_values, 5, true) << std::endl;
    std::cout << "part2: " << process(actual_values, 100, true) << std::endl;

}
