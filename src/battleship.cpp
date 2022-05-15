#include "../inc/battlefunc.h"
#include "../inc/algorithm.h"

board_tile game_board[10][10];
board_tile comp_board[10][10];

int main()
{
	// 	
 	battleship* comp_aircraft_carrier = (battleship*)malloc(sizeof(battleship));
	battleship* comp_battleship = (battleship*)malloc(sizeof(battleship));
  battleship* comp_sub = (battleship*)malloc(sizeof(battleship));
 	battleship* comp_cruiser = (battleship*)malloc(sizeof(battleship));
  battleship* comp_pt = (battleship*)malloc(sizeof(battleship));

 	battleship* user_aircraft_carrier = (battleship*)malloc(sizeof(battleship));
	battleship* user_battleship = (battleship*)malloc(sizeof(battleship));
  battleship* user_sub = (battleship*)malloc(sizeof(battleship));
 	battleship* user_cruiser = (battleship*)malloc(sizeof(battleship));
  battleship* user_pt = (battleship*)malloc(sizeof(battleship));

  // Initializing board tiles
  init_board();
  get_user_input(comp_pt, comp_sub, comp_cruiser,comp_battleship,comp_aircraft_carrier);
  init_comp_board(user_pt, user_sub, user_cruiser,user_battleship,user_aircraft_carrier);
  print_boards();

	// Declare relavent variables
  bool end_of_game = false;
  bool new_location = false;
  int x,y,counter = 0, counter2 =0;
	std::pair<int,int> comp_loc;

	// Set loop that runs until the end of the game
  while(!end_of_game){
    while(!new_location){ // prompts them until a new location and in the board
		  std::cout << "Enter the row cord you want to shoot at: ";
      std::cin >> x;
      std::cout << "Enter the col cord you want to shoot at: ";
      std::cin >> y;

			// Checks to see if the proposed hit is valid
      if((x >= 0 && x <= 9) && (y >= 0 && y <= 9)){
        if(comp_board[x][y].been_hit){
          std::cout << "Already been hit enter new coordinates" << std::endl;
        }
        else{
          comp_board[x][y].been_hit = true;
          new_location = true;
        }
      }
      else{
        std::cout << "Invalid coordinates, try again" << std::endl;
      }
    }
			
		// Check if there is a ship at the point that the user choose
		std::cout << std::flush;
		system("clear");
    new_location = false;
    if(comp_board[x][y].contains_ship){
      std::cout << "Hit!" << std::endl;
      comp_board[x][y].boat_pointer->ship_health -= 1;
      if(comp_board[x][y].boat_pointer->ship_health == 0){
        std::cout << "You sunk my " << comp_board[x][y].boat_pointer->name << "!" << std::endl;
        comp_board[x][y].boat_pointer->is_sunk = true;
				counter++;
      }
    }
    else{
      std::cout << "Miss!" << std::endl;
    }

	 // Check if the end of the game has happened
   if(counter == 5){   
     	std::cout << std::flush;
     	system("clear");
      print_boards();
      std::cout << "You've Won The Game!" << std::endl;
      return 0;
   }

	 // Generate the computer's move for this turn 
   comp_loc = get_comp_attack_coords(comp_pt,comp_sub,comp_cruiser,comp_battleship,comp_aircraft_carrier);
   comp_move(comp_loc,&counter2);

	 // Check if the computer has ended the game
   if(counter2 == 5){
    	std::cout << std::flush;
     	system("clear");
      print_boards();
      std::cout << "You Lost :( Better Luck Next Time!" << std::endl;
      return 0;
   }

	 // Print the boards
   print_boards();
		
   }  

   return 0;
    
}