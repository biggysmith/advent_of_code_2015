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

struct properties_t{
    int capacity = 0;
    int durability = 0;
    int flavor = 0;
    int texture = 0;
    int calories = 0;
};

struct ingredient_t{
    std::string name;
    properties_t props;
};

using ingredients_t = std::vector<ingredient_t>;

auto load_input(const std::string& file){
    ingredients_t ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){
        ingredient_t ingredient;
        char str0[20];
        sscanf(line.c_str(), "%s capacity %d, durability %d, flavor %d, texture %d, calories %d", str0, &ingredient.props.capacity, &ingredient.props.durability, &ingredient.props.flavor, &ingredient.props.texture, &ingredient.props.calories);
        ingredient.name = str0;
        ingredient.name.pop_back();
        ret.push_back(ingredient);
    }
    return ret;
}

void test_recipe(const ingredients_t& ingredients, std::vector<int>& teaspoons, int64_t& max_score, int ts, bool part1){
    if(ts < teaspoons.size()){
        for(int i=teaspoons[ts-1]; i<=100; ++i){
            teaspoons[ts] = i-teaspoons[ts-1];
            if(teaspoons[ts] !=  0){
                test_recipe(ingredients, teaspoons, max_score, ts+1, part1);
            }
        }
        return;
    }

    if(std::accumulate(teaspoons.begin(),teaspoons.end(),0) != 100){
        return;
    }

    properties_t props;
    for(int i=0; i<ingredients.size(); ++i){
        props.capacity += teaspoons[i] * ingredients[i].props.capacity;
        props.durability += teaspoons[i] * ingredients[i].props.durability;
        props.flavor += teaspoons[i] * ingredients[i].props.flavor;
        props.texture += teaspoons[i] * ingredients[i].props.texture;
        props.calories += teaspoons[i] * ingredients[i].props.calories;
    }

    int64_t score = std::max(0, props.capacity) * std::max(0, props.durability) * std::max(0, props.flavor) * std::max(0, props.texture);

    if(part1 || props.calories == 500){
        max_score = std::max(max_score, score);
    }
}

auto process(const ingredients_t& ingredients, bool part1)
{
    int64_t max_score = 0;

    std::vector<int> teaspoons(ingredients.size(), 0);
    for(int i=0; i<=100; ++i){
        teaspoons[0] = i;
        test_recipe(ingredients, teaspoons, max_score, 1, part1);
    }

    return max_score; 
}

void main()
{
    auto test_values = load_input("../src/day15/example_input.txt");
    auto actual_values = load_input("../src/day15/input.txt");

    std::cout << "part1: " << process(test_values, true) << std::endl;
    std::cout << "part1: " << process(actual_values, true) << std::endl;

    std::cout << "part2: " << process(test_values, false) << std::endl;
    std::cout << "part2: " << process(actual_values, false) << std::endl;
}
