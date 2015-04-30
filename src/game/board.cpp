
#include "board.h"
#include "game.h"
#include "../entities/water.h"
#include "../entities/physics/small.h"

#include <iostream>
#include <algorithm>

Board::Board(unsigned int _width, unsigned int _height, Game* _game):
		width(_width), height(_height), game(_game),
		topdata(std::vector<std::vector<Entity*>>(_width, std::vector<Entity*>(_height, nullptr))),
		data(std::vector<std::vector<std::vector<Entity*>>>(_width, std::vector<std::vector<Entity*>>(_height, std::vector<Entity*>(0))))
		{}

Entity* Board::get_top(unsigned int x, unsigned int y) {
	return topdata.at(x).at(y);
}

Entity* Board::get(unsigned int loc, unsigned int x, unsigned int y) {
	std::vector<Entity*>& spot = data.at(x).at(y);
	if (spot.size() > loc)
		return nullptr;
	return spot[loc];
}

bool Board::valid_location(int x, int y) {
	return ((0 <= x) && (x <= width) && (0 <= y) && (y <= height));
}

int Board::location_height(unsigned int x, unsigned int y) {
	int height = 0;
	for (auto e: data.at(x).at(y)) {
		height += e->get_height();
	}
	return height;
}

Entity* Board::leave_top_location(unsigned int x, unsigned int y) {
	Entity* e = topdata.at(x).at(y);
	if (e == nullptr) {
		// nothing to be seen here, move along
		return nullptr;
	}
	
	if (location_height(x,y) > 0) {
		// We IA_Leave the entity below.
		game->leave(e, data.at(x).at(y).at(0));
	}
	
	// Set this top location to nullptr, because we should leave it
	topdata.at(x).at(y) = nullptr;
	
	return e;
}

// returns whether the entity has fallen through
bool Board::enter_top_location(Entity* e, unsigned int x, unsigned int y) {
	if (e == nullptr) {
		return false;
	}
	e->x = x;
	e->y = y;
	std::cout << "Tadaa! " << e->to_char() << "\n";
	if (location_height(x,y) < 0) {
		// fallthrough
		enter_location(e, x, y);
		return true;
	} else {
		// not a fallthrough, collide if needed
		Entity* old_e = topdata.at(x).at(y);
		if (old_e == nullptr) {
			topdata.at(x).at(y) = e;
		} else {
			// collide the two entities
			game->collide(e, old_e);
			
			// Two entities can't be on the exact same (top) location at once.
			// So one has to dissappear. If one of the objects is dead, that one is deleted.
			// Otherwise, the 'old' entity is deleted.
			if (! e->is_alive()) {
				game->graveyard.push_back(e);
			} else {
				// the old one has to go, sadly.
				game->graveyard.push_back(old_e);
				topdata.at(x).at(y) = e;
			}
		}
		
		if (location_size(x,y) > 0) {
			// We IA_Enter the entity below.
			game->enter(e, data.at(x).at(y).at(0));
		}
		
		return false;
	}
}

void Board::enter_location(Entity* e, unsigned int x, unsigned int y) {
	// This function is basically the 'physics engine', together with enter_top_location
	std::vector<Entity*>& loc = data.at(x).at(y); // less typing
	unsigned int current_pos = 0;
	Water* lowest_water = nullptr;
	bool e_is_water = (dynamic_cast<Water*>(e) != nullptr);
	
	if (!e_is_water) {  // if e is water, just add it to the top by default.
		for (; current_pos < loc.size(); current_pos++) {
			Entity* collider = loc.at(current_pos);
			
			// When to continue: when the collider is water without being filled
			
			if (Water* w = dynamic_cast<Water*>(collider)) {
				// We're colliding with water!
				if (w->is_filled()) {
					break; // it's water, but we shouldn't be here anyway
				} else {
					lowest_water = w;
				}
			} else {
				// If it's not water, it shouldn't keep falling down
				break;
			}
		}
	}
	
	// At this point, current_pos should be the location.
	auto current_it = loc.begin() + current_pos;
	
	// Even if water contains it, it may still IA_Enter the object below.
	
	// Water never contains Smalls, they should slip in between Waters
	if (lowest_water != nullptr && !(dynamic_cast<Small*>(e) != nullptr)) {
		game->collide(lowest_water, e);  // puts e in w, kills e
		if (current_pos < loc.size()) {
			game->enter(lowest_water, loc.at(current_pos));
		}
	} else {
		loc.insert(current_it, e);
		if (current_pos+1 < loc.size()) {
			game->enter(e, loc.at(current_pos+1));
		}
	}
}


char Board::to_char(unsigned int x, unsigned int y) {
	// 0 means invisibility (not '0')
	Entity* top_entity = topdata.at(x).at(y);
	if (top_entity != nullptr) {
		char topc = top_entity->to_char();
		if (topc != 0) {
			return topc;
		}
	}
	
	char c = 0;
	std::vector<Entity*> loc = data.at(x).at(y);
	for (Entity* e: loc) {
		c = e->to_char();
		if (c != 0) {
			return c;
		}
	}
	
	return ' ';
}



void Board::print_sideview(unsigned int x, unsigned int y) {
	if (topdata.at(x).at(y) != nullptr)
		std::cout << ">> " << topdata.at(x).at(y)->to_char() << "\n";
	
	for (Entity* e: data.at(x).at(y)) {
		std::cout << ">  " << e->to_char() << "\n";
	}
	
	std::cout << "\n";
}



// Private

int Board::location_size(unsigned int x, unsigned int y) {
	return data.at(x).at(y).size();
}

int Board::get_width() {
	return width;
}

int Board::get_height() {
	return height;
}

