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

struct stats_t{
    int hit_points;
    int damage;
    int armor;
};

struct item_t{
    std::string name;
    int cost;
    int damage;
    int armor;
};

auto load_input(const std::string& file){
    stats_t ret;
    std::ifstream fs(file);
    std::string line;
    std::getline(fs, line);
    sscanf(line.c_str(), "Hit Points: %d", &ret.hit_points);
    std::getline(fs, line);
    sscanf(line.c_str(), "Damage: %d", &ret.damage);
    std::getline(fs, line);
    sscanf(line.c_str(), "Armor: %d", &ret.armor);
    return ret;
}

void attack(const stats_t& attacker, stats_t& defender){
    defender.hit_points -= std::max(1, attacker.damage - defender.armor);
}

bool fight(stats_t player, stats_t enemy)
{
    bool player_turn = true;

    while(player.hit_points > 0 && enemy.hit_points > 0)
    {
        if(player_turn){
            attack(player, enemy);
        }else{
            attack(enemy, player);
        }
    
        player_turn = !player_turn;
    }

    return player.hit_points > 0;
}

auto process(const stats_t& boss)
{
    std::vector<item_t> weapons = {
        { "Dagger",  8, 4, 0 },
        { "Shortsword", 10, 5, 0 },
        { "Warhammer", 25, 6, 0 },
        { "Longsword", 40, 7, 0 },
        { "Greataxe", 74, 8, 0 }
    };
    std::vector<item_t> armors = {
        { "Naked", 0, 0, 0 }, // i.e. no armor
        { "Leather", 13, 0, 1 },
        { "Chainmail", 31, 0, 2 },
        { "Splintmail", 53, 0, 3 },
        { "Bandedmail", 75, 0, 4 },
        { "Platemail", 102, 0, 5 }
    };
    std::vector<item_t> rings = {
        { "LeftRingless", 0, 0, 0 }, // i.e. no ring on left hand
        { "RightRingless", 0, 0, 0 }, // i.e. no ring on right hand
        { "Damage +1", 25, 1, 0 },
        { "Damage +2", 50, 2, 0 },
        { "Damage +3", 100, 3, 0 },
        { "Defense +1", 20, 0, 1 },
        { "Defense +2", 40, 0, 2 },
        { "Defense +3", 80, 0, 3 }
    };

    int min_gold = INT_MAX;
    int max_gold = 0;

    for(auto& weapon : weapons)
    {    
        for(auto& armor : armors)
        {  
            for(auto& ring0 : rings)
            {        
                for(auto& ring1 : rings)
                {
                    if(ring0.name == ring1.name){
                        continue;
                    }

                    stats_t player{
                        100,
                        weapon.damage + ring0.damage + ring1.damage,
                        armor.armor + ring0.armor + ring1.armor
                    };
                    int cost = weapon.cost + armor.cost + ring0.cost + ring1.cost;

                    if(fight(player, boss)){
                        min_gold = std::min(min_gold, cost);
                    }else{
                        max_gold = std::max(max_gold, cost);
                    }
                }
            }
        }
    }

    return std::make_pair(min_gold, max_gold);
}

void main()
{
    auto actual_values = load_input("../src/day21/input.txt");

    auto results = process(actual_values);

    std::cout << "part1: " << results.first << std::endl;
    std::cout << "part2: " << results.second << std::endl;
}
