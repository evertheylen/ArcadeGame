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
	_collide(a,b);
}

bool Game::properlyInitialized() {
	return (this == initCheck);
}

void Game::kill(Entity* a) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling kill");
	_kill(a);
}

void Game::enter(Entity* top, Entity* bottom) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling enter");
	_enter(top, bottom);
}

void Game::leave(Entity* top, Entity* bottom) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling leave");
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
	int size = actions.size();
	for (int i=0; i<size; i++) {
		do_action(out);
		
		if (ended) {
			out << "Game ended, stopping.\n";
			break;
		}
	}
}

void Game::do_action(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling do_action");
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
	return actions.size();
}

bool Game::is_ended() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling is_ended");
	return ended;
}


Player* Game::get_player(std::string& name) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_player");
	auto p = playermap.find(name);
	if (p == playermap.end()) {
		return nullptr;
	} else {
		return p->second;
	}
}


Monster* Game::get_monster(std::string& name) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_monster");
	auto m = monstermap.find(name);
	if (m == monstermap.end()) {
		return nullptr;
	} else {
		return m->second;
	}
}

Actor* Game::get_actor(std::string& name) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_actor");
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
	auto g = gatemap.find(name);
	if (g == gatemap.end()) {
		return nullptr;
	} else {
		return g->second;
	}
}

void Game::add_player(Player* p) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_player");
	playermap[p->get_name()] = p;
}


void Game::add_monster(Monster* m) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_monster");
	monstermap[m->get_name()] = m;
}

void Game::add_gate(Gate* g) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling add_gate");
	gatemap[g->get_name()] = g;
}


int Game::players_alive() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling players_alive");
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
	graveyard.push_back(e);
}


void Game::write_actions(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling write_actions");
	std::list<Action*> _actions = actions;
	if (_actions.size() == 0) {
		out << "Geen resterende bewegingen\n";
		return;
	}
	for (int i = 0; i < actions.size(); i++) {
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
	board = b;
}

void Game::save(std::ostream& level, std::ostream& action) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling save");
	level << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<VELD>\n\t<NAAM> " << board->get_name() << " </NAAM>\n";
	level << "\t<BREEDTE>" << board->get_width() << "</BREEDTE>\n\t<LENGTE>" << board->get_height() << "</LENGTE>\n";
	for (int i = board->get_height()-1; i>=0; i--) {
		for (int j = 0; j < board->get_width(); j++) {
			if (board->get_top(j,i) != nullptr) {
				level << "\t";
				board->get_top(j,i)->save(level, j, i);
				level << "\n";
			}
			for (int k = 0; k < board->location_size(j,i); k++) {
				Entity* e = board->get(k, j, i);
				level << "\t";
				e->save(level, j, i);
				level << "\n";
				if(Water* w = dynamic_cast<Water*>(e)) {
					if(w->contained != nullptr) {
						level << "\t\t\t";
						w->contained->save(level, j, i);
					}
					level << "\n\t\t</CONTAINED>\n\t</WATER>\n";
				}
			}
		}
	}
	level << "</VELD>\n";

	action << "<?xml version=\"1.0\" ?>\n<ACTIES>\n";
	int size = actions.size();
	std::list<Action*> _actions = actions;
	for (int i = 0; i < size; i++) {
		_actions.front()->save(action);
		_actions.pop_front();
		action << "\n";
	}
	action << "</ACTIES>\n";
}

Game::~Game() {
	for (Entity* e: graveyard) {
		delete e;
	}
	clear_actions();
	delete board;
}
