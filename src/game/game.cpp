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
		board(nullptr), ended(false) {}

/*Game::Game (Board* _board, std::list<Action*>* _actions, Playermap _players, Monstermap _monsters, Gatemap _gates):
	collide(this), enter(this), leave(this), kill(this), ended(false), board(1,1,this) {
	board = *_board;
	actions = *_actions;
	playermap = _players;
	monstermap = _monsters;
	gatemap = _gates;
}*/

void Game::do_all_actions(std::ostream& out) {
	for (int i=0; i<actions.size(); i++) {
		do_action(out);
		
		if (ended) {
			out << "Game ended, stopping.\n";
		}
	}
}

void Game::do_action(std::ostream& out) {
	if (actions.size() < 1) return;
	Action* a = actions.front();
	if (!a->execute(this)) {
		out << "Action was unsuccessfull.\n";
	}
	delete a;
	actions.pop_front();
}

int Game::get_num_actions() {
	return actions.size();
}

bool Game::is_ended() {
	return ended;
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

void Game::clear_actions() {
	for (Action* a: actions) {
		delete a;
	}
	actions.clear();
}

Board* Game::get_board() {
	return board;
}

void Game::set_board(Board* b) {
	board = b;
}



Game::~Game() {
	for (Entity* e: graveyard) {
		delete e;
	}
	clear_actions();
	delete board;
}
