#include <iostream>
#include <functional>

#include "game/game.h"
#include "events/eventmanager.h"

int main() {	
	//Game g(EventManager(std::cout));
	Game g;
	
	g.main_loop();
}


/*
 * TODO
 *  - Events based framework
 *  - Components
 *
 */
