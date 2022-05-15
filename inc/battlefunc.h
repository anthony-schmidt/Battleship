#ifndef BATTLEFUNC_H
#define BATTLEFUNC_H

#include <iostream>
#include <stack>
#include <cmath>
#include <stdlib.h> 
#include <time.h>
#include <string.h>

#include "globals.h"

extern board_tile game_board[10][10];
extern board_tile comp_board[10][10];

void init_board();
void print_boards();
//void print_board();
void get_user_input(battleship*, battleship*, battleship*, battleship*, battleship*);
void check_ship_spaces(int, battleship*);
bool check_board_spaces(int, int, int, int, int, board_tile [10][10], battleship*);
void init_comp_board(battleship*, battleship*, battleship*, battleship*, battleship*);
//void print_comp_board();
void start_game();



#endif
