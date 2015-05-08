
#include "attack.h"
#include "game.h"

#include <iostream>

Attack::Attack(Player* player, std::string& dirname):
		Action(player,dirname) {}


bool Attack::execute(Game* g) {
	unsigned int x = actor->x;
	unsigned int y = actor->y;
	dir.move_to(x,y);
	if (!g->get_board()->valid_location(x,y)) {
		return false; // invalid location
	}
	
	Entity* to_attack = g->get_board()->get_top(x,y);
	
	if (to_attack == nullptr) {
		return false; // nothing to attack
	} else {
		g->kill(to_attack);
		if (!to_attack->is_alive()) {
			g->get_board()->clear_top(x,y);
			g->bury(to_attack);
		}
	}
	
	return true;
}

void Attack::save(std::ostream& out) {
	Direction dir = get_dir();
	out << "\t<AANVAL>\n\t\t<ID>" << get_actor()->get_name() << "</ID>\n\t\t<RICHTING>" << dir << "</RICHTING>\n\t</AANVAL>";
}

