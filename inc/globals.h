#include <utility>
#include <vector>

#ifndef GLOBALS_H
#define GLOBALS_H



struct battleship{
   // Coordinates of Starting Point
   unsigned int start_x;
   unsigned int start_y;

   // Coordinates of Ending Point
   unsigned int end_x;
   unsigned int end_y;

   // length of the ship
   unsigned int ship_length;
   
   // health of the ship that the first time is the length of it
   unsigned int ship_health;

   //orientation of the ship vertical or horizontal 0 for horizontal 1 for vertical
   unsigned int orientation;

   bool is_sunk;

   char name[20];
	

	public:
		battleship(): start_x(), start_y(), end_x(), end_y(), ship_length(), ship_health(), orientation(), is_sunk(),name() {}


};

struct board_tile
{
   // Coordinates of tile
   unsigned int x;
   unsigned int y;

   // Is there a boat on the tile?
   bool contains_ship;
      
   // Has the tile already been hit by enemy fire?
   bool been_hit;

	// pointer to boat
	battleship* boat_pointer;

    public:
    	// Constructor
    	board_tile() : x(), y(), contains_ship(), been_hit(),boat_pointer() {}
    	void set_coords(unsigned int x_in, unsigned int y_in)
    	{
        	x = x_in; y = y_in;
    	}
        
};

extern board_tile game_board[10][10];
extern board_tile comp_board[10][10];

#endif
