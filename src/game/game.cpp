#include "game.h"
#include "../events/managers.h"

#include "../entities/entity.h"
#include "../entities/water.h"
#include "../entities/player.h"
#include "../entities/monster.h"
#include "../entities/barrel.h"
#include "../entities/button.h"
#include "../entities/gate.h"

#include "../actions/move.h"
#include "../actions/attack.h"

#include <iostream>
#include <typeinfo>
#include <string>


/*
void Game::event_log(std::string s) {
	em.log(s);
}
*/

Game::Game():
		collide(this), enter(this), leave(this), kill(this),
		board(10,10,this), ended(false) {}

/*Game::Game (Board* _board, std::list<Action*>* _actions, Playermap _players, Monstermap _monsters, Gatemap _gates):
	collide(this), enter(this), leave(this), kill(this), ended(false), board(1,1,this) {
	board = *_board;
	actions = *_actions;
	playermap = _players;
	monstermap = _monsters;
	gatemap = _gates;
}*/

void Game::main_loop() {
	// Currently example code.
	// TODO Check for this->ended
	
	/*
	Entity* e;
	Entity* f;
	
	e = new Water(3,2);
	f = new Player(4,5,"Mario");
	
	std::cout << e->to_char() << "\n";

	if (Water* w = dynamic_cast<Water*>(e)) {
		std::cout << "It's water!\n";
	}
	
	std::cout << "ended = " << ended << "\n";
	collide(e,f);
	std::cout << "ended = " << ended << "\n";
	kill(e);
	std::cout << "ended = " << ended << "\n";
	kill(f);
	std::cout << "ended = " << ended << "\n";
	
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
	std::cout << "afte enter\n";
	board.enter_location(w2,1,1);
	std::cout << "afte enter\n";
	board.enter_location(w3,1,1);
	std::cout << "afte enter\n";
	board.enter_location(w4,1,1);
	std::cout << "afte enter\n";
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

	add_player(pl1);
	std::cout << "players alive: " << players_alive() << "\n";
	
	auto m = new Monster(5,5,"Bowser");
	board.enter_top_location(m, 5, 5);
	
	std::cout << "players alive: " << players_alive() << "\n";
	
	std::cout << board.to_char(5, 5) << "\n";
	
	std::cout << "\n-------------------------------------------------------\n\n";
	
	std::string s = "OMHOOG";
	Move mooove(pl1, s);
// 	std::cout << mooove.dir << "\n";

	*/
	
	auto ba1 = new Barrel(2,1);
	auto ba2 = new Barrel(2,2);
	auto ba3 = new Barrel(2,3);
	
	auto ga1 = new Gate(4,1, "id");
	auto bu1 = new Button(3, 1, ga1);
	
	auto pl1 = new Player(5,5,"Mario");
	auto m = new Monster(5,5,"Bowser");
	
	board.enter_top_location(pl1, 0, 2);
	board.enter_top_location(ba1, 1, 2);
	board.enter_top_location(m,   2, 2);
	board.enter_top_location(ba2, 3, 2);
	board.enter_top_location(ba3, 4, 2);
	board.enter_location(bu1, 5, 2);
	
	std::string s = "RECHTS";
	Move mooove(pl1, s);
	
	std::cout << ga1->is_open() << "\n";
	
	mooove.execute(this);
	
	std::cout << ga1->is_open() << "\n";
}


Player* Game::get_player(std::string name) {
	auto p = playermap.find(name);
	if (p == playermap.end()) {
		return nullptr;
	} else {
		return p->second;
	}
}


Monster* Game::get_monster(std::string name) {
	auto m = monstermap.find(name);
	if (m == monstermap.end()) {
		return nullptr;
	} else {
		return m->second;
	}
}

Actor* Game::get_actor(std::string name) {
	// Players have priority if a player and monster have the same name
	Player* p = get_player(name);
	if (p != nullptr) {
		return p;
	} else {
		return get_monster(name);
	}
}


void Game::add_player(Player* p) {
	playermap[p->get_name()] = p;
}


void Game::add_monster(Monster* m) {
	monstermap[m->get_name()] = m;
}


int Game::players_alive() {
	int alive = 0;
	for (auto i: playermap) {
		if (i.second->is_alive()) {
			alive++;
		}
	}
	return alive;
}

void Game::bury(Entity* e) {
	graveyard.push_back(e);
}


void Game::write_actions(std::ostream& out) {
	std::list<Action*> _actions = actions;
	for (int i = 0; i < _actions.size(); i++) {
		std::string name = _actions.front()->get_actor()->get_name();
		bool player = true;
		if (playermap.find(name) == playermap.end()) {
			player = false;
		}
		if (player) {
			out << "Speler ";
		} else {
			out << "Monster ";
		}
		Direction dir = _actions.front()->get_dir();
		out << name << " zal volgende beweging nog uitvoeren:\n" << dir << "\n";
		_actions.pop_front();
	}
}
