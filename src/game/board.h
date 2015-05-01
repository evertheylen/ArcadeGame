/*
 * board.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include <iostream>
#include <vector>
#include <string>

#include "entity.h"


#ifndef _H_Board
#define _H_Board

class Game;

class Board {
public:
	Board(unsigned int _width, unsigned int _height, Game* _game);
	
	Entity* get_top(unsigned int x, unsigned int y);
	Entity* get(unsigned int loc, unsigned int x, unsigned int y);
	
	void set_name(std::string _name);

	bool valid_location(int x, int y);
	
	int location_height(unsigned int x, unsigned int y);
	
	Entity* leave_top_location(unsigned int x, unsigned int y);
	
	// returns whether the entity is fallen through (enter_location)
	bool enter_top_location(Entity* e, unsigned int x, unsigned int y);
	
	void enter_location(Entity* e, unsigned int x, unsigned int y);
	
	char to_char(unsigned int x, unsigned int y);
	
	void simple_graphics(std::ostream& out);

	void write_board(std::ostream& out);

	// For debugging only
	void print_sideview(unsigned int x, unsigned int y);
	
	int get_width();

	int get_height();

private:
	int location_size(unsigned int x, unsigned int y);
	
	Game* game;
	std::vector<std::vector<Entity*>> topdata;
	std::vector<std::vector<std::vector<Entity*>>> data;
	int width;
	int height;
	std::string name;
};


#endif
