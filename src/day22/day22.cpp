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
};

auto load_input(const std::string& file){
    stats_t ret;
    std::ifstream fs(file);
    std::string line;
    std::getline(fs, line);
    sscanf(line.c_str(), "Hit Points: %d", &ret.hit_points);
    std::getline(fs, line);
    sscanf(line.c_str(), "Damage: %d", &ret.damage);
    return ret;
}

struct state_t{
    int boss_hitpoints;
    int boss_damage;

    int mana = 500;
    int player_hitpoints = 50;
    int shield_strength = 0;
    int shield_timer = 0;
    int poison_timer = 0;
    int recharge_timer = 0;
    int mana_cost = 0;
};

enum spell_enum_t { e_magic_missle=0, e_drain, e_sheild, e_poison, e_recharge };

void apply_effects(state_t& state)
{
    state.shield_timer--;
    state.poison_timer--;
    state.recharge_timer--;

    if(state.shield_timer >= 0){
        state.shield_strength = 7;
    }else{
        state.shield_strength = 0;
    }

    if(state.poison_timer >= 0){
        state.boss_hitpoints -= 3;
    }

    if(state.recharge_timer >= 0){
        state.mana += 101;
    }
}

void dfs(state_t state, spell_enum_t spell, int& min_mana, bool part2)
{    
    // player turn
    if(part2){
        state.player_hitpoints--;
        if(state.player_hitpoints <= 0){
            return; // player dead, bail
        }
    }

    apply_effects(state);
    if (state.boss_hitpoints <= 0){
        min_mana = std::min(min_mana, state.mana_cost);
        return; // boss dead, bail
    }

    if(spell == e_magic_missle){
        state.boss_hitpoints -= 4;
        state.mana -= 53;
        state.mana_cost += 53;
    }
    else if(spell == e_drain){
        state.boss_hitpoints -= 2;
        state.player_hitpoints += 2;
        state.mana -= 73;
        state.mana_cost += 73;
    }
    else if(spell == e_sheild){
        state.mana -= 113;
        state.mana_cost += 113;
        if(state.shield_timer <= 0) {
            state.shield_timer = 6;
        }else{
            return; // can only cast when shield not already active, bail
        }
    }
    else if(spell == e_poison){
        state.mana -= 173;
        state.mana_cost += 173;
        if(state.poison_timer <= 0) {
            state.poison_timer = 6;
        }else{
            return; // can only cast when poison not already active, bail
        }
    }
    else if(spell == e_recharge){
        state.mana -= 229;
        state.mana_cost += 229;
        if(state.recharge_timer <= 0) {
            state.recharge_timer = 5;
        }else{
            return; // can only cast when recharge not already active, bail
        }
    }

    if(state.mana <= 0){
        return; // not enough mana, dead
    }

    if(state.mana_cost > min_mana){
        return; // push us over the current found min, bail
    }

   
    // boss turn
    apply_effects(state);
    if (state.boss_hitpoints <= 0){
        min_mana = std::min(min_mana, state.mana_cost);
        return; // boss dead, bail
    }

    state.player_hitpoints -= std::max(1, state.boss_damage - state.shield_strength);
    if(state.player_hitpoints <= 0){
        return; // player dead, bail
    }

    // next player turns
    dfs(state, e_magic_missle, min_mana, part2);
    dfs(state, e_drain, min_mana, part2);
    dfs(state, e_sheild, min_mana, part2);
    dfs(state, e_poison, min_mana, part2);
    dfs(state, e_recharge, min_mana, part2);
}

auto process(const stats_t& boss, bool part2)
{
    int min_mana = INT_MAX;

    state_t state { boss.hit_points, boss.damage };

    dfs(state, e_magic_missle, min_mana, part2);
    dfs(state, e_drain, min_mana, part2);
    dfs(state, e_sheild, min_mana, part2);
    dfs(state, e_poison, min_mana, part2);
    dfs(state, e_recharge, min_mana, part2);

    return min_mana;
}

void main()
{
    auto actual_values = load_input("../src/day22/input.txt");

    std::cout << "part1: " << process(actual_values, false) << std::endl;
    std::cout << "part2: " << process(actual_values, true) << std::endl;
}
