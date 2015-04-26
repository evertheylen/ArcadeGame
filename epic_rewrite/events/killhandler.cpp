
#include "killhandler.h"
#include "game.h"

#include <iostream>

void KillHandler::onKill(Entity* e) {
	e->kill();
	std::cout << "Entity was killed (but it might have survived).\n";
}

void KillHandler::onKill(Player* p) {
	p->kill();
	std::cout << "Player died! End the game!\n";
	if (game->players_alive() <= 0) {
		game->ended = true;
	}
}

void KillHandler::onKill(Alive* a) {
	a->kill();
}

// Immutables don't care
