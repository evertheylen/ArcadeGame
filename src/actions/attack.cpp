
#include "attack.h"
#include "game.h"

#include <iostream>

Attack::Attack(Player* player, std::string& dirname):
		Action(player,dirname) {}


bool Attack::execute(Game* g) {
	unsigned int x = actor->x;
	unsigned int y = actor->y;
	dir.move_to(x,y);
	if (!g->board.valid_location(x,y)) {
		return false; // invalid location
	}
	
	Entity* to_attack = g->board.get_top(x,y);
	
	if (to_attack == nullptr) {
		return false; // nothing to attack
	} else {
		g->kill(to_attack);
		if (!to_attack->is_alive()) {
			g->board.clear_top(x,y);
			g->bury(to_attack);
		}
	}
	
	return true;
}

