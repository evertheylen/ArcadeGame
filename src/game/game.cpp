#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>
#include <cstdlib>

#include "../../lib/tinyxml/tinyxml.h"
#include "game.h"
#include "../DesignByContract.h"
#include "board/barrel.h"
#include "board/wall.h"
#include "action/action.h"

// copy constructor
Game::Game(const Game& that):
	_board(that._board),
	_actions(),
	_players() {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Game& Game::operator=(const Game& that) {
	_board = that._board;
	_actions = std::list<Movement>();
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::list<Movement>& Game::get_actions() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_actions");
	return _actions;
}

Game::Game(Board* board, std::list< Movement >& actions, Game::Playermap& players):
	_board(board),
	_actions(actions),
	_players(players){
	_initCheck = this;
	ENSURE(properlyInitialized(), "Constructor of Game did not end properly.");
}

bool Game::properlyInitialized() const {
	return _initCheck == this;
}

void Game::writeBoard(std::ostream& stream) {
	stream << *_board << "\n";

	/*Het huidige speelveld is Level 1:
	Eigenschappen van dit veld:
	-Breedte 10
	-Lengte 10*/

	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeBoard");

	stream << "Het huidige speelveld is " << _board->get_name() << ":\n"
			<< "Eigenschappen van dit veld:\n"
			<< "-Breedte " << _board->get_width() << "\n"
			<< "-Lengte " << _board->get_height() << "\n\n";

	// Find all the stuff that isn't a wall
	for (unsigned int i = 0; i != _board->get_width(); i++) {
		for (unsigned int j = 0; j != _board->get_height(); j++) {
			(*_board)(i,j)->writeThings(stream);
		}
	}
}

void Game::writeActions(std::ostream& stream) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeActions");
	if (_actions.empty()) {
		stream << "geen acties\n";
		return;
	}
	for (auto i: _actions) {
		stream << i << std::endl;
	}
}

void Game::popAction(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling popAction");
	REQUIRE(!_actions.empty(), "Actions was empty, can't be popped");
	unsigned int original_size = _actions.size();
	doMove(_actions.front(), out);
	_actions.pop_front();
	ENSURE(_actions.size() == original_size - 1, "Action was not popped");
}

void Game::doAction(Action& action, std::ostream& out) {
/*	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doMove");
	unsigned int x = movement.get_player()->get_x();
	unsigned int y = movement.get_player()->get_y();
	unsigned int x_original = x;
	unsigned int y_original = y;
	//out << movement << std::endl;
	//std::cout << (*_board)(x,y)->is_movable() << "\n";
	
	if (! _board->valid_location(x,y)) {
		out << "Error: Not a valid location. Skipping movement.\n";
		return;
	}
	
	// calculate total weight
	unsigned int x_next = x;
	unsigned int y_next = y;
	// calculate new location
	doDirection(movement.get_dir(), x_next, y_next);  // x or y are modified
	int total_weight = 0;
	// while not out of board and not an empty spot

	while (_board->valid_location(x_next, y_next) && (*_board)(x_next, y_next) != nullptr) {
		if ((*_board)(x_next, y_next)->get_weight() == -1) {
			out << "Error: Can't move infinite weight (like a wall), skipping this movement.\n";
			return;
		}
		total_weight += (*_board)(x_next, y_next)->get_weight();
		doDirection(movement.get_dir(), x_next, y_next);
	}
	
	if (! _board->valid_location(x_next, y_next)) {
		out << "Error: Out of board. Skipping this movement.\n";
		return;
	}
	
	if ((*_board)(x_next, y_next) != nullptr) {
		out << "Error: Player (and perhaps other things) have no place to go. Skipping this movement.\n";
		return;
	}
		
	if (total_weight > movement.get_player()->get_maximum_weight()) {
		out << "Error: Player tries to move too much weight. Skipping this movement.\n";
		return;
	}
	
	// move all things, we work backwards
	unsigned int x_new = x_next;
	unsigned int y_new = y_next;
	doReverseDirection(movement.get_dir(), x_new, y_new);
	while (x_next != x || y_next != y) {
		Thing* temp = (*_board)(x_new, y_new);
		(*_board)(x_new, y_new) = nullptr; //(*_board)(x_next, y_next);
		
		(*_board)(x_next, y_next) = temp;
		if ((*_board)(x_next, y_next) != nullptr) {
			(*_board)(x_next, y_next)->set_x(x_next);
			(*_board)(x_next, y_next)->set_y(y_next);
		}
		x_next = x_new;
		y_next = y_new;
		doReverseDirection(movement.get_dir(), x_new, y_new);
	}
 	doDirection(movement.get_dir(), x, y);
// 	movement.get_player()->set_x(x);
// 	movement.get_player()->set_y(y);
	ENSURE(x_original != x || y_original != y, "Movement not completed, location remained the same.");*/
}

void Game::doAllActions(std::ostream& out) {
	/*REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doAllMoves");
	out << "About to do all " << _actions.size() << " actions.\n\n";
	//out << _board << "\nStarting now:\n";
	
	while (! _actions.empty()) {
// 		out << _board << "\n";
		popMove(out);
	}
// 	out << _board << "\n";
	out << "Done.\n";

	ENSURE(get_actions().empty(), "Not all actions were executed.");*/
}
