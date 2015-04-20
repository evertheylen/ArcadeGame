#include <iostream>
#include <functional>

#include "game/game.h"
#include "UI/UI.h"

int main() {	
	//Game g(EventManager(std::cout));
	Game g;
	
	g.main_loop();

	UI user_interface;
}


/*
 * TODO
 *  - Events based framework
 *  - Components
 *
 */
