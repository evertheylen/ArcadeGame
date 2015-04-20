
#include "killhandler.h"
#include <iostream>

void KillHandler::onKill(Entity* e) {
	e->kill();
	std::cout << "Entity was killed (but it might have survived).\n";
}

void KillHandler::onKill(Player* p) {
	p->kill();
	std::cout << "Player died!\n";
}

