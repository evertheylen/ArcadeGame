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
#include "movement/movement.h"

// copy constructor
Game::Game(const Game& that):
	_board(that._board),
	_movements(),
	_players() {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Game& Game::operator=(const Game& that) {
	_board = that._board;
	_movements = std::list<Movement>();
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::list<Movement>& Game::get_movements() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_movements");
	return _movements;
}

Game::Game(TiXmlDocument& board_doc, TiXmlDocument& moves_doc, std::ostream& out) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Constructor of Game did not end properly.");
}

bool Game::properlyInitialized() const {
	return _initCheck == this;
}

/*bool Game::reqElement(TiXmlElement* elem, const char* tag) {
	TiXmlElement* e = elem->FirstChildElement(tag);
	if (e == NULL) {
		return false;
	}
	return true;
}

void Game::parsePlayer(TiXmlElement* elem, std::ostream& out) {
	try {
		TiXmlElement* current_el = elem->FirstChildElement();
		if (elem == NULL) {
			out << "Error: Error while parsing obstacle, no first child. Skipping.\n";
			return;
		}
		std::string name;
		if (!reqElement(elem, "NAAM")) {
			out << "Error: Player must have a name specified. Skipping.\n";
			return;
		}
		
		while (current_el != NULL) {
			if (current_el->ValueTStr() == "NAAM") {
				name = readElement(current_el);
			} else {
				out << "Error: Error: Tag " << current_el->Value() << " not defined.\n";
			}

			current_el = current_el->NextSiblingElement();
		}
		
		int x, y;
		try {
			x = std::stoi(readAttribute(elem, "x"));
			y = std::stoi(readAttribute(elem, "y"));
		} catch (std::invalid_argument& e) {
			out << "Error: Invalid x or y specified for player, skipping.\n";
			return;
		}
		
		if (! _board.valid_location(x,y)) {
			out << "Error: Invalid location given. Skipping player.\n";
			return;
		}
		
		if (_board(x,y) != nullptr) {
			out << "Error: Specified location of player not empty. Skipping.\n";
			return;
		}
		
		if (_players.find(name) != _players.end()) {
			out << "Error: Player already exists. Skipping.\n";
			return;
		}
		
		Player* player = new Player(name, x, y);
		_players[name] = player;

		// Put on board

		_board(x, y) = player;

		//std::cout << _players[name].get_name() << std::endl;
	} catch (ParseError& e) {
		out << "Error: Error while parsing player. Skipping.\n";
		return;
	}
}

void Game::parseObstacle(TiXmlElement* elem, std::ostream& out) {
	try {
		TiXmlElement* current_el = elem->FirstChildElement();
		if (elem == NULL) {
			out << "Error: Error while parsing obstacle, no first child. Skipping.\n";
			return;
		}
		
		std::string type;
		if (!reqElement(elem, "TYPE")) {
			out << "Error: Obstacle must have a type specified.\n";
			return;
		}
		
		while (current_el != NULL) {
			if (current_el->ValueTStr() == "TYPE") {
				type = readElement(current_el);
			} else {
				out << "Error: Error: tag " << current_el->Value() << " not defined.\n";
			}

			current_el = current_el->NextSiblingElement();
		}
		
		int x,y;
		try {
			x = std::stoi(readAttribute(elem, "x"));
			y = std::stoi(readAttribute(elem, "y"));
		} catch (std::invalid_argument& e) {
			out << "Error: Invalid x or y specified for obstacle, skipping.\n";
			return;
		}
		
		if (! _board.valid_location(x,y)) {
			out << "Error: Invalid location given. Skipping obstacle.\n";
			return;
		}
		
		if (_board(x,y) != nullptr) {
			out << "Error: Specified location of obstacle not empty. Skipping.\n";
			return;
		}
		
		Thing* obst;
		if (type == "ton") {
			if (readAttribute(elem, "beweegbaar") != "true") {
				out << "Error: Error: A barrel must be declared movable.\n";
			} else {
				obst = new Barrel(x, y);
				// Put on board
				_board(x, y) = obst;
			}
		} else if (type == "muur") {
			if (readAttribute(elem, "beweegbaar") != "false") {
				out << "Error: Error: A wall may not be declared movable.\n";
			} else {
				obst = new Wall(x, y);
				// Put on board
				_board(x, y) = obst;
			}
		} else {
			out << "Error: Error: Type " << type << " is not defined as an obstacle.\n";
		}
	} catch (ParseError& e) {
		out << "Error: Error while parsing obstacle. Skipping.\n";
		return;
	}
	
}

std::string Game::readElement(TiXmlElement* elem, const char* tag) {
	if (elem == NULL) {
		//out << "Error: Error: Tag not defined.";
		throw(ParseError());
	}
	TiXmlElement* e = elem->FirstChildElement(tag);
	if (elem == NULL) throw(ParseError());
	TiXmlNode* node = e->FirstChild();
	if (node == NULL) throw(ParseError());
	TiXmlText* text = node->ToText();
	return text->Value();
}

std::string Game::readElement(TiXmlElement* elem) {
	if (elem == NULL) {
		//out << "Error: Error: Tag not defined.";
		throw(ParseError());
	}
	TiXmlNode* node = elem->FirstChild();
	if (node == NULL) throw(ParseError());
	TiXmlText* text = node->ToText();
	return text->Value();
}

std::string Game::readAttribute(TiXmlElement* elem, const char* tag) {
	if (elem == NULL) {
		throw(ParseError());
	}
	return std::string(elem->Attribute(tag));
}*/

void Game::writeBoard(std::ostream& stream) {
	stream << _board << "\n";

	/*Het huidige speelveld is Level 1:
	Eigenschappen van dit veld:
	-Breedte 10
	-Lengte 10*/

	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeBoard");

	stream << "Het huidige speelveld is " << _board.get_name() << ":\n"
			<< "Eigenschappen van dit veld:\n"
			<< "-Breedte " << _board.get_width() << "\n"
			<< "-Lengte " << _board.get_height() << "\n\n";

	// Find all movable Things.
	for (unsigned int i = 0; i != _board.get_width(); i++) {
		for (unsigned int j = 0; j != _board.get_height(); j++) {
			if (_board(i,j) != nullptr && _board(i,j)->is_movable()) {
				stream << *_board(i,j) << "\n";
			}
		}
	}
}

void Game::writeMovements(std::ostream& stream) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeMovements");
	if (_movements.empty()) {
		stream << "geen bewegingen\n";
		return;
	}
	for (auto i: _movements) {
		stream << i << std::endl;
	}
}

void Game::popMove(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling popMove");
	REQUIRE(!_movements.empty(), "Movements was empty, can't be popped");
	unsigned int original_size = _movements.size();
	doMove(_movements.front(), out);
	_movements.pop_front();
	ENSURE(_movements.size() == original_size - 1, "Movement was not popped");
}

void Game::doMove(Movement& movement, std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doMove");
	unsigned int x = movement.get_player()->get_x();
	unsigned int y = movement.get_player()->get_y();
	unsigned int x_original = x;
	unsigned int y_original = y;
	//out << movement << std::endl;
	//std::cout << _board(x,y)->is_movable() << "\n";
	
	if (! _board.valid_location(x,y)) {
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

	while (_board.valid_location(x_next, y_next) && _board(x_next, y_next) != nullptr) {
		if (_board(x_next, y_next)->get_weight() == -1) {
			out << "Error: Can't move infinite weight (like a wall), skipping this movement.\n";
			return;
		}
		total_weight += _board(x_next, y_next)->get_weight();
		doDirection(movement.get_dir(), x_next, y_next);
	}
	
	if (! _board.valid_location(x_next, y_next)) {
		out << "Error: Out of board. Skipping this movement.\n";
		return;
	}
	
	if (_board(x_next, y_next) != nullptr) {
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
		Thing* temp = _board(x_new, y_new);
		_board(x_new, y_new) = nullptr; //_board(x_next, y_next);
		
		_board(x_next, y_next) = temp;
		if (_board(x_next, y_next) != nullptr) {
			_board(x_next, y_next)->set_x(x_next);
			_board(x_next, y_next)->set_y(y_next);
		}
		x_next = x_new;
		y_next = y_new;
		doReverseDirection(movement.get_dir(), x_new, y_new);
	}
 	doDirection(movement.get_dir(), x, y);
// 	movement.get_player()->set_x(x);
// 	movement.get_player()->set_y(y);
	ENSURE(x_original != x || y_original != y, "Movement not completed, location remained the same.");
}

void Game::doAllMoves(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doAllMoves");
	out << "About to do all " << _movements.size() << " movements.\n\n";
	//out << _board << "\nStarting now:\n";
	
	while (! _movements.empty()) {
// 		out << _board << "\n";
		popMove(out);
	}
// 	out << _board << "\n";
	out << "Done.\n";

	ENSURE(get_movements().empty(), "Not all movements were executed.");
}
