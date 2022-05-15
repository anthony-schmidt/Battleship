#include "../inc/battlefunc.h"
#include "math.h"

// These two loops initialize the boards and the structs with them
void init_board()
{
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      game_board[i][j].set_coords(i,j);
      game_board[i][j].contains_ship = false;
      game_board[i][j].been_hit = false;
    }
  }

  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      comp_board[i][j].set_coords(i,j);
      comp_board[i][j].contains_ship = false;
      comp_board[i][j].been_hit = false;
    }
  }
}

// This function prints the currects boards with ASCII color components
void print_boards()
{
	std::cout << "      COMPUTER BOARD		  	   YOUR BOARD" << std::endl << std::endl;

	std::cout << "   0 1 2 3 4 5 6 7 8 9			   0 1 2 3 4 5 6 7 8 9" << std::endl;
	std::cout << "  ————————————————————			  ————————————————————" << std::endl;

	for(unsigned int i = 0; i < 10; i++)
	{ 
		std::cout << i << "| ";
		for(unsigned int j = 0; j < 10; j++)
		{
			if (comp_board[i][j].contains_ship && comp_board[i][j].been_hit)
			{	
				std::cout <<"\033[0;31m"<< "H" << "\033[0m" << " ";
			}
			else if (!comp_board[i][j].contains_ship && comp_board[i][j].been_hit)
			{
				std::cout << "\033[0;34m";
				std::cout << "M" << "\033[0m" << " ";
			}
			else
			{
				std::cout << "0" << " ";
			}	
			
		}

		std::cout << "			" << i << "| ";

		for(unsigned int j = 0; j < 10; j++)
		{
			if (game_board[i][j].contains_ship && !game_board[i][j].been_hit)
			{
				std::cout <<"\033[0;32m"<< "S" << "\033[0m" << " ";
			}
			else if (game_board[i][j].contains_ship && game_board[i][j].been_hit)
			{
				std::cout <<"\033[0;31m"<< "H" << "\033[0m" << " ";
			}
			else if (!game_board[i][j].contains_ship && game_board[i][j].been_hit)
			{
				std::cout << "\033[0;34m";
				std::cout << "M" << "\033[0m" << " ";
			}
			else
			{
				std::cout << "0" << " ";
			}	
		}
		std::cout << std::endl;
	}
}

// This function gets the ship locations that the user wants to put on the computer's board
void get_user_input(battleship* user_pt, battleship* user_sub, battleship* user_cruiser, battleship* user_battleship, battleship* user_aircraft_carrier){
  
	// initialize the battleships all locations 0,0 with their length, health, orientation set, unsunk
  user_aircraft_carrier->ship_length = 5;
  user_aircraft_carrier->ship_health = 5;
  strcpy(user_aircraft_carrier->name,"Aircraft Carrier");

  user_battleship->ship_length = 4;
  user_battleship->ship_health = 4;
  strcpy(user_battleship->name,"Battleship");

  user_sub->ship_length = 3;
  user_sub->ship_health = 3;
  strcpy(user_sub->name,"Submarine"); 
 
  user_cruiser->ship_length = 3;
  user_cruiser->ship_health = 3;
  strcpy(user_cruiser->name,"Cruiser"); 

  user_pt->ship_length = 2;
  user_pt->ship_health = 2;
  strcpy(user_pt->name,"Patrol Torpedo Boat"); 

	system("clear");
  std::cout << "Decide the location of the Aircraft Carrier(length 5)" << std::endl;
  check_ship_spaces(5,user_aircraft_carrier);
  std::cout << std::endl << std::flush;
	system("clear");
  std::cout << "Decide the location of the Battleship(length 4)" << std::endl;
  check_ship_spaces(4,user_battleship);
  std::cout << std::endl << std::flush;
	system("clear");
  std::cout << "Decide the location of the Submarine(length 3)" << std::endl;
  check_ship_spaces(3,user_sub);
  std::cout << std::endl << std::flush;
	system("clear");
  std::cout << "Decide the location of the Cruiser(length 3)" << std::endl;
  check_ship_spaces(3,user_cruiser);
  std::cout << std::endl << std::flush;
	system("clear");
  std::cout << "Decide the location of the Patrol Torpedo Boat(length 2)" << std::endl;
  check_ship_spaces(2,user_pt);
	std::cout << std::flush;
	system("clear");
	
}

// This function checks the spaces on the ship to make sure that they are valid
void check_ship_spaces(int len,battleship* curr_ship){
  int x1,y1,x2,y2;
  bool boat_placed = false;

  while(!boat_placed){
    print_boards();
    std::cout << "Enter the row location that you want to start at: "; 
    std::cin >> x1;
    std::cout << "Enter the col location that you want to start at: ";
    std::cin >> y1;
    std::cout << "Enter the row location that you want to end at: "; 
    std::cin >> x2;
    std::cout << "Enter the col location that you want to end at: ";
    std::cin >> y2;

    boat_placed = check_board_spaces(x1,y1,x2,y2,len,game_board,curr_ship); 
    if(!boat_placed){
			std::cout << std::flush;
			system("clear");
      std::cout << "Incorrect locations selected, cannot be diagonal, must be correct length and cannot overlap" << std::endl;
			std::cout << "Retry Entering: " << curr_ship->name << " (Length " << len << ")"<< std::endl;
    }
  }
}

// This is another checker of the validity of a board space that was chosen
bool check_board_spaces(int x1, int y1, int x2, int y2, int len, board_tile curr_board[10][10], battleship* curr_ship){
  if((x1 != x2 && y1 != y2) || (x1 < 0 || x1 > 9 || y1 < 0 || y1 > 9 || x2 < 0 || x2 > 9 || y2 < 0 || y2 > 9)){
    return false;
  }

  else{
    if(x1 == x2){
      if(std::abs(y2-y1) + 1 != len){
        return false;
      }
      if(y1 < y2){
        for(int i = y1; i <= y2; i++){
          if(curr_board[x1][i].contains_ship)
            return false;
        }
      }
      else{
        for(int i = y2; i <= y1; i++){
          if(curr_board[x1][i].contains_ship)
            return false;
        }
      }
    }

    else{
      if(std::abs(x2-x1) + 1 != len){
        return false;
      }
      if(x1 < x2){
        for(int i = x1; i <= x2; i++){
          if(curr_board[i][y1].contains_ship)
            return false;
        }
      }
      else{
        for(int i = x2; i <= x1; i++){
          if(curr_board[i][y1].contains_ship)
            return false;
        }
      }
    }    
  }

  // if it gets down here it worked so update board and return true
  if(x1 == x2){ // set all the spaces to contain a ship and update their boat pointer
    if(y1 < y2){ // means horizontal and y1 is starting point
      curr_ship->start_x = x1;
      curr_ship->start_y = y1;
      curr_ship->end_x = x2;
      curr_ship->end_y = y2;
      curr_ship->orientation = 0;

      for(int i = y1; i <= y2; i++){
        curr_board[x1][i].contains_ship = true;
        curr_board[x1][i].boat_pointer = curr_ship; // point space to whatever ship
      }
    }
    else{
      curr_ship->start_x = x1; // otherwise y2 is starting point
      curr_ship->start_y = y2;
      curr_ship->end_x = x2;
      curr_ship->end_y = y1;
      curr_ship->orientation = 0;

      for(int i = y2; i <= y1; i++){
        curr_board[x1][i].contains_ship = true;
        curr_board[x1][i].boat_pointer = curr_ship;
      }
    }
  }

  else{
    if(x1 < x2){ // means vertical and x1 is starting point
      curr_ship->start_x = x1;
      curr_ship->start_y = y1;
      curr_ship->end_x = x2;
      curr_ship->end_y = y2;
      curr_ship->orientation = 1;

      for(int i = x1; i <= x2; i++){
        curr_board[i][y1].contains_ship = true;
        curr_board[i][y1].boat_pointer = curr_ship;
      }
    }
    else{ // means vertical and x2 is the starting point
      curr_ship->start_x = x2;
      curr_ship->start_y = y1;
      curr_ship->end_x = x1;
      curr_ship->end_y = y2;
      curr_ship->orientation = 1;

      for(int i = x2; i <= x1; i++){
        curr_board[i][y1].contains_ship = true;
        curr_board[i][y1].boat_pointer = curr_ship;
      }
    }
  }
  
  curr_ship->is_sunk = false;
  return true;
}

// This creates ships to put on the user board and checks if a certain ship is able to be placed a certain way
void init_comp_board(battleship* comp_pt, battleship* comp_sub, battleship* comp_cruiser, battleship* comp_battleship, battleship* comp_aircraft_carrier){
  // generate the ship locations randomly, no strategy involved but can be changed later
  srand ((unsigned int)time(NULL)); // initialize time seed for random number
  int x1, y1, x2, y2; // four randomly generated numbers to decide boat locations

  int orientation, front_or_behind; // two ints to determine how ship is placed

  bool is_placed = false; // boolean to run while loop similar to user placement

  // initialize boats
  comp_aircraft_carrier->ship_length = 5;
  comp_aircraft_carrier->ship_health = 5;
  strcpy(comp_aircraft_carrier->name,"Aircraft Carrier");

  comp_battleship->ship_length = 4;
  comp_battleship->ship_health = 4;
  strcpy(comp_battleship->name,"Battleship");

  comp_sub->ship_length = 3;
  comp_sub->ship_health = 3;
  strcpy(comp_sub->name,"Submarine"); 
 
  comp_cruiser->ship_length = 3;
  comp_cruiser->ship_health = 3;
  strcpy(comp_cruiser->name,"Cruiser"); 

  comp_pt->ship_length = 2;
  comp_pt->ship_health = 2;
  strcpy(comp_pt->name,"Patrol Torpedo Boat");
 
  for(int i = 5; i > 1; i--){ // do ships from len 5 to len 2
    while(!is_placed){
      x1 = rand() % 10; // two random numbers 0 through 9 for first location
      y1 = rand() % 10;

      orientation = rand() % 2; // random number just used to determine orientaiton, either make vertical if odd make horizontal either 0 or 1
      front_or_behind = rand() % 2; // random number to either add or subtract length either 0 or 1

      if(orientation == 0){ // horizontal so x2 is the same as x1, y is either len infront or behind
        x2 = x1;
        if(front_or_behind == 0){
          y2 = y1 + i;
        }
        else{
          y2 = y1 - i;
        }
      }
      else{ // vertical so y2 is the same as y1, x is either len infront or behind
        y2 = y1;
        if(front_or_behind == 0){
          x2 = x1 + i - 1;
        }
        else{
          x2 = x1 - i + 1;
        }
      }
      if(i == 5)
        is_placed = check_board_spaces(x1,y1,x2,y2,i,comp_board,comp_aircraft_carrier);
      else if(i == 4)
        is_placed = check_board_spaces(x1,y1,x2,y2,i,comp_board,comp_battleship);
      else if(i == 3)
			{
       	is_placed = check_board_spaces(x1,y1,x2,y2,i,comp_board,comp_sub);
      // 	is_placed = check_board_spaces(x1,y1,x2,y2,i,comp_board,comp_cruiser);
			}
      else if(i == 2)
        is_placed = check_board_spaces(x1,y1,x2,y2,i,comp_board,comp_pt);
      //std::cout << x1 << "," << y1 << " " << x2 << "," << y2 << std::endl;
    } 
  is_placed = false;
  }
  // do it again for 3 since there are two boats of len 3
  while(!is_placed){
    x1 = rand() % 10; // two random numbers 0 through 9 for first location
    y1 = rand() % 10;

    orientation = rand() % 2; // random number just used to determine orientaiton, either make vertical if odd make horizontal either 0 or 1
    front_or_behind = rand() % 2; // random number to either add or subtract length either 0 or 1

    if(orientation == 0){ // horizontal so x2 is the same as x1, y is either len infront or behind
      x2 = x1;
      if(front_or_behind == 0){
        y2 = y1 + 2;
      }
      else{
        y2 = y1 - 2;
      }
    }
    else{ // vertical so y2 is the same as y1, x is either len infront or behind
      y2 = y1;
      if(front_or_behind == 0){
        x2 = x1 + 2;
      }
      else{
        x2 = x1 - 2;
      }
    }
    is_placed = check_board_spaces(x1,y1,x2,y2,3,comp_board,comp_cruiser);
  }
	
}