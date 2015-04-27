
#include "attack.h"
#include "game.h"

#include <iostream>

Attack::Attack(Player* player, std::string& dirname):
		Action(player,dirname) {}


void Attack::execute(Game* g) {
	std::cout << "Execute attack " << dir;
}

