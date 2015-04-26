
#include "ia_enterhandler.h"
#include "constants.h"
#include "game.h"

#include <iostream>

void IA_EnterHandler::onEnter(Entity* e, Entity* f) {
	std::cout << "unhandled enter " << e->x << ", " << e->y << ";; " << f->x << ", " << f->y << "\n";
}

void IA_EnterHandler::onEnter(Entity* e, Button* b) {
	if (e->get_weight() > BUTTON_ACTIVATE_FROM) {
		b->gate->open();
		std::cout << "Gate open!\n";
	} else {
		std::cout << "Not opening Gate, not enough weight\n";
	}
}

void IA_EnterHandler::onEnter(Player* p, Goal* g) {
	// TODO Game should end
	std::cout << "Game should end!!!!!!!!!!!!\n";
}

void IA_EnterHandler::onEnter(Actor* a, Boobytrap* b) {
	game->kill(a);
	game->kill(b);
}


