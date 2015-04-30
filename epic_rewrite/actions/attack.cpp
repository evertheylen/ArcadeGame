
#include "attack.h"
#include "game.h"

#include <iostream>

Attack::Attack(Player* player, std::string& dirname):
		Action(player,dirname) {}


void Attack::execute(Game* g) {
	unsigned int x = actor->x;
	unsigned int y = actor->y;
	dir.move_to(x,y);
	
	if (!g->board.valid_location(x,y)) {
		std::cout << "Invalid location\n";
	} else if (g->board.get_top(x,y) == nullptr) {
		std::cout << "Nothing to attack\n";
	} else {
		g->kill(g->board.get_top(x,y));
	}
}

