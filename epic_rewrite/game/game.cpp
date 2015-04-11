#include "game.h"
#include "../events/event.h"
#include "../entities/entity.h"

#include <iostream>
#include <typeinfo>

Game::Game(EventManager _em):
		em(_em) {
	em.set_game(this);
}

void Game::event_log(std::string s) {
	em.log(s);
}

void Game::main_loop() {
	// Currently example code.
	Entity a;
	Entity b;
	
	auto e = Collision<Entity, Entity>(a,b);
	std::cout << typeid(e).name() << "\n";
	em.push(&e);
}

