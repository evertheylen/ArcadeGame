#include "game.h"
#include "../events/managers.h"
#include "../entities/entity.h"
#include "../entities/water.h"
#include "../entities/player.h"
#include "../entities/monster.h"
#include "../entities/barrel.h"
#include "../entities/button.h"
#include "../entities/gate.h"

#include <iostream>
#include <typeinfo>


/*
void Game::event_log(std::string s) {
	em.log(s);
}
*/

Game::Game():
		collide(this), enter(this), leave(this), kill(this),
		board(10,10,this) {}


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
	
	collide(e,f);
	
	kill(e);
	kill(f);
	
	delete e;
	delete f;
	
	std::cout << "\n-------------------------------------------------------\n\n";
	
	auto w1 = new Water(1,1);
	auto w2 = new Water(1,2);
	auto w3 = new Water(1,3);
	auto w4 = new Water(1,4);
	
	auto ba1 = new Barrel(2,1);
	auto ba2 = new Barrel(2,2);
	auto ba3 = new Barrel(2,3);
	
	auto ga1 = new Gate(4,1);
	auto bu1 = new Button(3, 1, ga1);
	
	//board = Board(10,10,this);
	board.enter_location(w1,1,1);
	board.enter_location(w2,1,1);
	board.enter_location(w3,1,1);
	board.enter_location(w4,1,1);
	board.print_sideview(1,1);
	std::cout << "\n----------------\n\n";
	
	board.enter_location(ba1, 1, 1);
	board.print_sideview(1,1);
	std::cout << "\n----------------\n\n";
	
	board.enter_location(bu1, 1, 1);
	board.print_sideview(1,1);
	std::cout << "\n----------------\n\n";
	
	board.enter_location(ba2, 1, 1);
	board.print_sideview(1,1);
	std::cout << "\n----------------\n\n";
	
	std::cout << board.to_char(1, 1) << "\n";
	
	std::cout << "\n-------------------------------------------------------\n\n";
	
	auto pl1 = new Player(5,5,"Mario");
	board.enter_top_location(pl1, 5, 5);
	
	auto m = new Monster(5,5,"Bowser");
	board.enter_top_location(m, 5, 5);
	
	std::cout << board.to_char(5, 5) << "\n";
}

