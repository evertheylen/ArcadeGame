#include "game.h"
#include "../events/managers.h"
#include <events/collisionmanager.h>

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
		_collide(this), _enter(this), _leave(this), _kill(this),
		board(nullptr), ended(false) {
	initCheck = this;
	ENSURE(properlyInitialized(), "Constructor must end...");
}

void Game::collide(Entity* a, Entity* b) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling collide");
	REQUIRE(board != nullptr, "Board wasn't specified");
	_collide(a,b);
}

bool Game::properlyInitialized() {
	return (this == initCheck);
}

void Game::kill(Entity* a) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling kill");
	REQUIRE(board != nullptr, "Board wasn't specified");
	_kill(a);
}

void Game::enter(Entity* top, Entity* bottom) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling enter");
	REQUIRE(board != nullptr, "Board wasn't specified");
	_enter(top, bottom);
}

void Game::leave(Entity* top, Entity* bottom) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling leave");
	REQUIRE(board != nullptr, "Board wasn't specified");
	_leave(top, bottom);
}


/*Game::Game (Board* _board, std::list<Action*>* _actions, Playermap _players, Monstermap _monsters, Gatemap _gates):
	collide(this), enter(this), leave(this), kill(this), ended(false), board(1,1,this) {
	board = *_board;
	actions = *_actions;
	playermap = _players;
	monstermap = _monsters;
	gatemap = _gates;
}*/

void Game::do_all_actions(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling do_all_actions");
	REQUIRE(board != nullptr, "Board wasn't specified");
	for (int i=0; i<actions.size(); i++) {
		do_action(out);
		
		if (ended) {
			out << "Game ended, stopping.\n";
		}
	}
}

void Game::do_action(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling do_action");
	REQUIRE(board != nullptr, "Board wasn't specified");
	if (actions.size() < 1) return;
	Action* a = actions.front();
	if (!a->execute(this)) {
		out << "Action was unsuccessfull.\n";
	}
	delete a;
	actions.pop_front();
}

int Game::get_num_actions() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_num_actions");
	REQUIRE(board != nullptr, "Board wasn't specified");
	return actions.size();
}

bool Game::is_ended() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling is_ended");
	REQUIRE(board != nullptr, "Board wasn't specified");
	return ended;
}


Player* Game::get_player(std::string& name) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_player");
	REQUIRE(board != nullptr, "Board wasn't specified");
	auto p = playermap.find(name);
	if (p == playermap.end()) {
		return nullptr;
	} else {
		return p->second;
	}
}


Monster* Game::get_monster(std::string& name) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_monster");
	REQUIRE(board != nullptr, "Board wasn't specified");
	auto m = monstermap.find(name);
	if (m == monstermap.end()) {
		return nullptr;
	} else {
		return m->second;
	}
}

Actor* Game::get_actor(std::string& name) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_actor");
	REQUIRE(board != nullptr, "Board wasn't specified");
	// Players have priority if a player and monster have the same name
	Player* p = get_player(name);
	if (p != nullptr) {
		return p;
	} else {
		return get_monster(name);
	}
}

Gate* Game::get_gate(std::string& name) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_gate");
	REQUIRE(board != nullptr, "Board wasn't specified");
	auto g = gatemap.find(name);
	if (g == gatemap.end()) {
		return nullptr;
	} else {
		return g->second;
	}
}


void Game::add_player(Player* p) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_player");
	REQUIRE(board != nullptr, "Board wasn't specified");
	playermap[p->get_name()] = p;
}


void Game::add_monster(Monster* m) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_monster");
	REQUIRE(board != nullptr, "Board wasn't specified");
	monstermap[m->get_name()] = m;
}

void Game::add_gate(Gate* g) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_gate");
	REQUIRE(board != nullptr, "Board wasn't specified");
	gatemap[g->get_name()] = g;
}


int Game::players_alive() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling players_alive");
	REQUIRE(board != nullptr, "Board wasn't specified");
	int alive = 0;
	for (auto i: playermap) {
		if (i.second->is_alive()) {
			alive++;
		}
	}
	return alive;
}

void Game::bury(Entity* e) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling bury");
	REQUIRE(board != nullptr, "Board wasn't specified");
	graveyard.push_back(e);
}


void Game::write_actions(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling write_actions");
	REQUIRE(board != nullptr, "Board wasn't specified");
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

void Game::clear_actions() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling clear_actions");
	REQUIRE(board != nullptr, "Board wasn't specified");
	for (Action* a: actions) {
		delete a;
	}
	actions.clear();
}

Board* Game::get_board() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_board");
	REQUIRE(board != nullptr, "Board wasn't specified");
	return board;
}

void Game::set_board(Board* b) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling set_board");
	REQUIRE(board != nullptr, "Board wasn't specified");
	board = b;
}



Game::~Game() {
	for (Entity* e: graveyard) {
		delete e;
	}
	clear_actions();
	delete board;
}
