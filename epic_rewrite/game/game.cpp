#include "game.h"
#include "../events/managers.h"
#include "../entities/entity.h"
#include "../entities/water.h"

#include <iostream>
#include <typeinfo>


/*
void Game::event_log(std::string s) {
	em.log(s);
}
*/

Game::Game():
		collide(this), enter(this), leave(this) {}


void Game::main_loop() {
	// Currently example code.
	
	Entity* e;
	Entity* f;
	
	e = new Water(3,2);
	f = new Water(2,3);
	
	std::cout << e->to_char() << "\n";

	if (Water* w = dynamic_cast<Water*>(e)) {
		std::cout << "It's water!\n";
	}
	
	/*if (Container* c = dynamic_cast<Container*>(e)) {
		std::cout << "It's a container!\n";
	}*/		// TODO Ik kan momenteel niet checken op container omdat container geen aparte klasse meer is...
			// Water is echter het enige dat een container kan zijn dus is da ni een beetje overbodig om dan een aparte klasse te maken?
	
	collide(e,f);

	/*
	auto e = Collision<Entity, Entity>(a,b);
	em.push(e);
	
	auto f = Collision<Water, Entity>(w, b);
	em.push(f);
	*/
	
	delete e;
	delete f;
}

