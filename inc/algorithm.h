#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <utility>
#include <random>
#include <vector>
#include <math.h>
#include <stdio.h>

#include "globals.h"

bool can_be_hit(int i, int j);
void check_rotation(int ship_size_min1, int i, int j);
void check_shifts(int ship_size_min1, int i, int j);
void prob_board_logic_find(int ship_size);
void update_prob_board_find(battleship* p_tp, battleship* p_sub, battleship* p_cruiser, battleship* p_battle_ship, battleship* p_carrier);
int get_max();
std::pair<int, int> fill_possible_attacks(std::vector<std::pair<int, int>> possible_attack_vec, int max);
std::pair<int, int> get_comp_attack_coords(battleship* p_tp, battleship* p_sub, battleship* p_cruiser, battleship* p_battle_ship, battleship* p_carrier);
bool comp_ship_attacked(battleship* p_tp, battleship* p_sub, battleship* p_cruiser, battleship* p_battle_ship, battleship* p_carrier);
void comp_move(std::pair<int,int> comp_loc, int* counter);
void attack_coords_finder();
void print_boards_a();

#endif

/*EXTRAS
void print_boards();
void prob_board_logic_destroy(int ship_size);
void update_prob_board_destroy(bool tp_living, bool sub_living, bool cruiser_living, bool battleship_living, bool carrier_living);
*/
