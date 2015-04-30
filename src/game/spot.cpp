/*
#include "spot.h"
#include "game.h"

Spot::Spot (Game* _game):
		game(_game), top(nullptr), rest(0) {}

Entity* Spot::get_top() {
	return top;
}

void Spot::set_top(Entity* e) {
	top = e;
	if (rest.size() > 0) {
		game->enter(top, rest[0]);
	}
	
	// TODO fallthrough enzo
}
*/
