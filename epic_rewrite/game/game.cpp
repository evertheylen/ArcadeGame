#include "game.h"
#include "../events/managers.h"
#include "../entities/entity.h"
#include "../entities/water.h"
#include "../entities/player.h"

#include <iostream>
#include <typeinfo>


/*
void Game::event_log(std::string s) {
	em.log(s);
}
*/

Game::Game():
		collide(this), enter(this), leave(this), kill(this) {}


void Game::main_loop() {
	// Currently example code.
	
	Entity* e;
	Entity* f;
	
	e = new Water(3,2);
	f = new Player(4,5,"Mario");
	
	std::cout << e->to_char() << "\n";

	if (Water* w = dynamic_cast<Water*>(e)) {
		std::cout << "It's water!\n";
	}
	
	int a = collide(e,f);
	std::cout << a << "\n";
	
	kill(e);
	kill(f);
	
	delete e;
	delete f;
}

