#include "game.h"
#include "../events/event.h"
#include "../entities/entity.h"
#include "../entities/water.h"

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

Game::Game() {}	//TODO REMOVE THIS SON OF A BITCH == this is temporary code, don't forget to remove it once it isn't necessary anymore.

void Game::main_loop() {
	// Currently example code.
	
	Entity* e;
	
	if (5==5) {
		e = new Water(3,2);
	}
	
	std::cout << e->to_char() << "\n";

	if (Water* w = dynamic_cast<Water*>(e)) {
		std::cout << "It's water!\n";
	}
	
	/*if (Container* c = dynamic_cast<Container*>(e)) {
		std::cout << "It's a container!\n";
	}*/		// TODO Ik kan momenteel niet checken op container omdat container geen aparte klasse meer is...
			// Water is echter het enige dat een container kan zijn dus is da ni een beetje overbodig om dan een aparte klasse te maken?
	
	/*
	auto e = Collision<Entity, Entity>(a,b);
	em.push(e);
	
	auto f = Collision<Water, Entity>(w, b);
	em.push(f);
	*/
	
	delete e;
}

