/**********************
 * algorithm.cpp
 *
 * File Contents: This file contains the computer algorithm where the computer decides which spot on the board has the 
 * highest probability of a hit.
 *
 * Project Team: Daniel Schermerhorn, David Chirumbole, Daniel Schermerhorn, Landon Bachman
 **********************/

#include <iostream>
#include <utility>
#include <random>
#include <vector>
#include <math.h>
#include <stdio.h>

#include "../inc/algorithm.h"

int prob_board[10][10] = 
{
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// This determines if a spot on the computer's board can be hit
bool can_be_hit(int i, int j){
    if((i < 0) | (j < 0)){
        return false;
    }
    
    if((i > 9) | (j > 9)){
        return false;
    }
    
    if(game_board[i][j].been_hit == true){
        return false;
    }
    
    return true;
    
}

// This function checks for different rotations of ships that a hit could possibly have on a certain space
void check_rotation(int ship_size_min1, int i, int j){
    int k = 0;
    int counter = 0;
    for(k = ship_size_min1; k > 0; k--){
        if(!can_be_hit(i, j + k)){
            counter++; 
        }
    }
    if(counter == 0){
        prob_board[i][j]++;
    }
    counter = 0;
    
    for(k = ship_size_min1; k > 0; k--){
        if(!can_be_hit(i, j - k)){
           counter++; 
        }
    }
    if(counter == 0){
        prob_board[i][j]++;
    }
    counter = 0;
    
    for(k = ship_size_min1; k > 0; k--){
        if(!can_be_hit(i + k, j)){
           counter++; 
        }
    }
    if(counter == 0){
        prob_board[i][j]++;
    }
    counter = 0;
    
    for(k = ship_size_min1; k > 0; k--){
        if(!can_be_hit(i - k, j)){
           counter++; 
        }
    }
    if(counter == 0){
        prob_board[i][j]++;
    }
    counter = 0;
}

// This program combines with the others to create the probability board that is used to determine the best place on the board for the 
// computer to hit
void check_shifts(int ship_size_min1, int i, int j){
    int num_shifts = ship_size_min1 - 1;
    for(int k = num_shifts; k > 0; k--){
        if(can_be_hit(i - k, j) && can_be_hit(i + k, j)){
            prob_board[i][j]++;
        }
        if(can_be_hit(i, j - k) && can_be_hit(i, j + k)){
            prob_board[i][j]++;
        }
    }
}

// This function goes through all the rotations and shifts to add to the probability board
void prob_board_logic_find(int ship_size){
    int ship_size_min1 = ship_size - 1;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(can_be_hit(i, j)){
                check_rotation(ship_size_min1, i, j);
                check_shifts(ship_size_min1, i, j);
            }
        }
    }
}

// This function updates the final probability board according to which ships are not sunk yet
void update_prob_board_find(battleship* p_tp, battleship* p_sub, battleship* p_cruiser, battleship* p_battle_ship, battleship* p_carrier){
    if(!p_tp->is_sunk){
        prob_board_logic_find(p_tp->ship_length);
    }
    if(!p_sub->is_sunk){
        prob_board_logic_find(p_sub->ship_length);
    }
    if(!p_cruiser->is_sunk){
        prob_board_logic_find(p_cruiser->ship_length);
    }
    if(!p_battle_ship->is_sunk){
        prob_board_logic_find(p_battle_ship->ship_length);
    }
    if(!p_carrier->is_sunk){
        prob_board_logic_find(p_carrier->ship_length);
    }
}

// This gets the max probability of a spot on the probability board
int get_max(){
    int max = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(prob_board[i][j] > max){
                max = prob_board[i][j];
            }
        }
    }
    return max;
}

// This returns a possible spot for the computer to attack using an std::pair
std::pair<int, int> fill_possible_attacks(std::vector<std::pair<int, int>> possible_attack_vec, int max){
    int k = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(prob_board[i][j] == max){
                possible_attack_vec.push_back(std::make_pair(i, j));
                k++;
            }
        }
    }
    
    srand((unsigned int) time(NULL));
    long unsigned int rand_index = rand() % possible_attack_vec.size();
    return possible_attack_vec[rand_index];
}

// This function is within the scope of the attack portion of the algorithm and checks all the spots around the coord that was hit
void attack_coords_finder()
{
   std::pair<int, int> attack_loc;
   std::vector< std::pair <int,int>> possible_coords;
   int counter = 0;

   for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
         if(game_board[i][j].been_hit && game_board[i][j].contains_ship && game_board[i][j].boat_pointer->ship_health != 0){
            attack_loc = std::make_pair(i, j);

            if(can_be_hit(attack_loc.first - 1, attack_loc.second)){
               prob_board[attack_loc.first - 1][attack_loc.second] = 1;
               counter++;
            }
            if(can_be_hit(attack_loc.first + 1, attack_loc.second)){
               prob_board[attack_loc.first + 1][attack_loc.second] = 1;
               counter++;
            }
            if(can_be_hit(attack_loc.first , attack_loc.second - 1)){
               prob_board[attack_loc.first][attack_loc.second - 1] = 1;
               counter++;
            }
            if(can_be_hit(attack_loc.first, attack_loc.second + 1)){
               prob_board[attack_loc.first][attack_loc.second + 1] = 1;
               counter++;
            }

            if(counter != 0){
               possible_coords.push_back(attack_loc);
            }
            counter = 0;
         }
      }
   }

   long unsigned int size = possible_coords.size();
   long unsigned int row_temp;
   long unsigned int col_temp;

   for(long unsigned int i = 0; i < size; i++){
      row_temp = possible_coords[i].first;
      col_temp = possible_coords[i].second;
      for(long unsigned int j = 0; j < 10; j++){
         if(game_board[row_temp][j].been_hit && game_board[row_temp][j].contains_ship && game_board[row_temp][j].boat_pointer->ship_health != 0 && j != col_temp){
            for(long unsigned int k = 0; k < 10; k++){
               prob_board[row_temp][k] *= 2;
            }
         }
      }

      for(long unsigned int j = 0; j < 10; j++){
         if(game_board[j][col_temp].been_hit && game_board[j][col_temp].contains_ship && game_board[j][col_temp].boat_pointer->ship_health != 0 && j != row_temp){
             for(long unsigned int k = 0; k < 10; k++){
               prob_board[k][col_temp] *= 2;
            }
         }
      }
   }
}

// This function acts as the quasi-main function of algorithm.cpp and directs the computer to choose between updating the probability board the normal
// way and updating the probability board if there is an attack
std::pair<int, int> get_comp_attack_coords(battleship* p_tp, battleship* p_sub, battleship* p_cruiser, battleship* p_battle_ship, battleship* p_carrier){
    std::vector<std::pair<int, int>> possible_attack_vec;
    std::pair<int, int> the_pair;

   for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
         prob_board[i][j] = 0;
      }
   }

    if(comp_ship_attacked(p_tp, p_sub, p_cruiser, p_battle_ship, p_carrier)){
		   attack_coords_finder();
    }
    else{
        update_prob_board_find(p_tp, p_sub, p_cruiser, p_battle_ship, p_carrier);
    }

   int max = get_max();
   the_pair = fill_possible_attacks(possible_attack_vec, max);

    return the_pair;
}

// This function shows if there is an unresolved hit on the board
bool comp_ship_attacked(battleship* p_tp, battleship* p_sub, battleship* p_cruiser, battleship* p_battle_ship, battleship* p_carrier){

 	if((p_tp->ship_length > p_tp->ship_health) && (p_tp->ship_health != 0))
	{
		return true;
	}

 	if((p_sub->ship_length > p_sub->ship_health) && (p_sub->ship_health != 0))
	{
		return true;
	}
		
 	if((p_cruiser->ship_length > p_cruiser->ship_health) && (p_cruiser->ship_health != 0))
	{
		return true;
	}
		
 	if((p_battle_ship->ship_length > p_battle_ship->ship_health) && (p_battle_ship->ship_health != 0))
	{
		return true;
	}
		
 	if((p_carrier->ship_length > p_carrier->ship_health) && (p_carrier->ship_health != 0))
	{
		return true;
	}
	
	return false;
}

// This function is similar to what goes on in main but if sees if the computer makes a hit and updates the board accordingly
void comp_move(std::pair<int,int> comp_loc,int *counter2)
{
	int x,y;
	x = comp_loc.first;
	y = comp_loc.second;
	std::cout << "Computer Attacks: " << comp_loc.first << "," << comp_loc.second << std::endl;
	game_board[comp_loc.first][comp_loc.second].been_hit = true;
  if(game_board[x][y].contains_ship){
      std::cout << "The Computer Hit!" << std::endl;
      game_board[x][y].boat_pointer->ship_health -= 1;
      if(game_board[x][y].boat_pointer->ship_health == 0){
        std::cout << "The computer sunk your " << game_board[x][y].boat_pointer->name << "!" << std::endl;
        game_board[x][y].boat_pointer->is_sunk = true;
				(*counter2)++;
      } 
	}
  else{
    std::cout << "The Computer Missed!" << std::endl;
  }
}


//REFERENCES
//https://paulvanderlaken.com/2019/01/21/beating-battleships-with-algorithms-and-ai/
//https://www.csuohio.edu/sites/default/files/82B-2016.pdf
