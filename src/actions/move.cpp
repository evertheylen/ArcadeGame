
#include "move.h"
#include "../game/game.h"
#include "../entities/constants.h"
#include "../entities/actor.h"

#include <iostream>

Move::Move(Actor* _actor, std::string& dirname):
		Action(_actor, dirname) {}


bool Move::execute(Game* g) {
	unsigned int start_x = actor->x;
	unsigned int start_y = actor->y;
	if (g->get_board()->get_top(start_x, start_y) != actor) {
		return false;
	}
// 	std::cout << "Moving " << actor->get_name() << " from " << start_x << ", " << start_y;
	unsigned int next_x = start_x;
	unsigned int next_y = start_y;
	dir.move_to(next_x, next_y);
	// check for valid next location
// 	std::cout << " to " << next_x << ", " << next_y << std::endl;
	if (!g->get_board()->valid_location(next_x, next_y) || (g->get_board()->location_height(next_x, next_y) > 0)) {
// 		std::cout << "Error: not a valid location or height (next)\n";
		return false;
	}
	
	// Two possibilities:
	//   1) the location we're moving to contains an Actor (not nullptr)
	//   2) not ^
	
	if (Actor* loc_a = dynamic_cast<Actor*>(g->get_board()->get_top(next_x, next_y))) {
		g->get_board()->leave_top_location(start_x, start_y);
		// Simply enter loc_a into the board
		g->get_board()->enter_top_location(actor, next_x, next_y);
	} else {
		// calculate total_weight and valid end location
		// all the objects that need to move are: [start, ..., current,] next
		// and they need to move to:               start, [..., current, next]
		int total_weight = 0;
		
		unsigned int current_x = start_x;
		unsigned int current_y = start_y;
		
		while (true) {
			if (g->get_board()->get_top(next_x, next_y) == nullptr) {
				// good, there's an empty spot for us
				break;
			}
			
			dir.move_to(current_x, current_y);
			dir.move_to(next_x, next_y);

			total_weight += g->get_board()->get_top(current_x, current_y)->get_weight();

			// valid end location is empty, not out of board, not height > 0
			if ( !(g->get_board()->valid_location(next_x, next_y)) || (g->get_board()->location_height(next_x, next_y) > 0)) {
				// error: we can't push...
				return false;
			}
			
		}
		
// 		std::cout << "total_weight = " << total_weight << "\n";
// 		std::cout << "next = (" << next_x << ", " << next_y << ")\n";
		
		// check total_weight > ACTOR_POWER
		if (total_weight > ACTOR_POWER) {
// 			std::cout << "Error: actor tries to push too much weight\n";
			return false;
		}
		
		// move all stuff (work backwards)
		do {
			Entity* e = g->get_board()->leave_top_location(current_x, current_y);
			g->get_board()->enter_top_location(e, next_x, next_y);  // also takes care of setting e->x and y.
			
			dir.move_from(current_x, current_y);
			// current may end up pointing at a wrong location (unsigned int max?), but it doesn't matter.
			// the while loop will stop anyway in such a situation.
			dir.move_from(next_x, next_y);
			
// 			std::cout << "next = (" << next_x << ", " << next_y << ")\n";
		} while (next_x != start_x || next_y != start_y);
	}
	
	return true;
}

