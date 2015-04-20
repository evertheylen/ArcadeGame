/*
 * board.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include <vector>

#include "entity.h"

#ifndef _H_Board
#define _H_Board

class Game;

class Board {
public:
	Board(unsigned int _width, unsigned int _height, Game* _game);
	
	Entity* get_top(unsigned int x, unsigned int y);
	Entity* get(unsigned int loc, unsigned int x, unsigned int y);
	
	int loc_height(unsigned int x, unsigned int y);
	
	void leave_location(unsigned int x, unsigned int y);
	
	
private:
	Game* game;
	std::vector<std::vector<Entity*>> topdata;
	std::vector<std::vector<std::vector<Entity*>>> data;
	int width;
	int height;
};


#endif
