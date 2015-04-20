
#include "board.h"
#include "game.h"

Board::Board(unsigned int _width, unsigned int _height, Game* _game):
		width(_width), height(_height), game(_game),
		topdata(std::vector<std::vector<Entity*>>(width, std::vector<Entity*>(height, nullptr))),
		data(std::vector<std::vector<std::vector<Entity*>>>(width, std::vector<std::vector<Entity*>>(height, std::vector<Entity*>(0))))
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

Entity* Board::leave_location(unsigned int x, unsigned int y) {
	Entity* e = topdata.at(x).at(y);
	if (e == nullptr) {
		// nothing to be seen here, move along
		return nullptr;
	}
	
	if (location_height(x,y) > 0) {
		// We IA_Leave the entity below.
		game->leave(e, data.at(x).at(y).at(0));
	}
	
	return e;
}

// returns whether the entity has fallen through
bool Board::enter_top_location(Entity* e, unsigned int x, unsigned int y) {
	if (location_height() < 0) {
		// fallthrough
		enter_location(e, x, y);
		return false;
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
			if (! old_e->is_alive()) {
				delete old_e;
				topdata.at(x).at(y) = e;
			} else if (! e->is_alive()) {
				delete e;
			} else {
				// the old one has to go, sadly.
				delete old_e;
				topdata.at(x).at(y) = e;
			}
		}
		return false;
	}
}

void Board::enter_location(Entity * e, unsigned int x, unsigned int y) {
	// This function is basically the 'physics engine', together with enter_top_location
	int current_pos = 0;
	std::vector<Entity*>& loc = data.at(x).at(y);
}


// Private

int Board::location_size(unsigned int x, unsigned int y) {
	return data.at(x).at(y).size();
}

