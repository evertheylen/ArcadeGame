#include "game.h"
#include "../events/event.h"
#include "../entities/entity.h"
#include "../entities/water.h"
#include "../entities/physics/container.h"

#include <iostream>
#include <typeinfo>

/*
Game::Game(EventManager _em):
		em(_em) {
	em.set_game(this);
}
*/



/*
void Game::event_log(std::string s) {
	em.log(s);
}
*/

void Game::main_loop() {
	// Currently example code.
	
	Entity* e;
	
	if (5==5) {
		e = new Water;
	}
	
	std::cout << e->to_char() << "\n";

	if (Water* w = dynamic_cast<Water*>(e)) {
		std::cout << "It's water!\n";
	}
	
	if (Container* c = dynamic_cast<Container*>(e)) {
		std::cout << "It's a container!\n";
	}
	
	/*
	auto e = Collision<Entity, Entity>(a,b);
	em.push(e);
	
	auto f = Collision<Water, Entity>(w, b);
	em.push(f);
	*/
	
	delete e;
}

