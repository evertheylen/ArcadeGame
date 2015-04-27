
#include "move.h"
#include "../game/game.h"
#include "../entities/constants.h"

#include <iostream>

Move::Move(Actor* _actor, std::string& dirname):
		Action(_actor, dirname) {}


void Move::execute(Game* g) {
	// check for valid start location
	int start_x = actor->x;
	int start_y = actor->y;
	g->board.valid_location(start_x, start_y);
	
	// calculate total_weight and valid end location
		// valid end location is empty, not out of board, not height > 0
	
	// check total_weight < ACTOR_POWER
	
	// move all stuff (work backwards)
		// leave location
		// enter location
		// set x and y for all entities
	
}

