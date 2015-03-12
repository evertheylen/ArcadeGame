#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept>

#include "../../lib/tinyxml/tinyxml.h"
#include "game.h"
#include "../DesignByContract.h"
#include "board/barrel.h"
#include "board/wall.h"
#include "movement/movement.h"

std::list<Movement>& Game::get_movements() {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling get_movements");
	return _movements;
}

Game::Game(TiXmlDocument& board_doc, TiXmlDocument& moves_doc) {
	
	// ---- Board ----
	TiXmlElement* root = board_doc.FirstChildElement();
	REQUIRE(root != NULL, "Failed to load board file: No root element.");
	// Warning, for some mysterious reason, root->Value() == "VELD" will always fail, even if it should definitly pass.
	REQUIRE(root->ValueTStr() == "VELD", "Failed to load board file: Wrong root element tag.");
	
	TiXmlElement* current_el = root->FirstChildElement();
	std::string boardname;
	_players = Playermap();

	int x, y;
	try {
		x = std::stoi(readElement(root, "BREEDTE"));
		y = std::stoi(readElement(root, "LENGTE"));
	} catch (std::invalid_argument& e) {
		REQUIRE(false, "Invalid BREEDTE or LENGTE in board file.");
	}
	
	if (_board.valid_location(x,y)) {
		std::cerr << "Invalid board dimensions.\n";
		return;
	}
	
	_board = Board(x, y);

	//TODO Test if all necessary elements are specified in the xml file. Else error! I think this is done for the most part???

	while (current_el != NULL) {
		if (current_el->ValueTStr() == "NAAM") {
			boardname = readElement(current_el);
			_board.set_name(boardname);
		} else {
			if (current_el->ValueTStr() == "SPELER") {
				parsePlayer(current_el);
			} else {
				if (current_el->ValueTStr() == "OBSTAKEL") {
					parseObstacle(current_el);
				} else {
					if (current_el->ValueTStr() != "BREEDTE"
							&& current_el->ValueTStr() != "LENGTE") {
						std::cerr << "Error: tag " << current_el->Value() << " not defined.\n";
						/*ss << "Error: tag " << current_el->Value() << " not defined.\n";
						std::string str = ss.str();
						ss.str("");
						REQUIRE(false, str.c_str());*/
					}
				}
			}
		}
		current_el = current_el->NextSiblingElement();
	}


	// ---- Movements ----
	root = moves_doc.FirstChildElement();
	REQUIRE(root != NULL, "Failed to load movements file: No root element.");
	REQUIRE(root->ValueTStr() == "BEWEGINGEN", "Failed to load movements file: Wrong root element tag.");
	current_el = root->FirstChildElement();
	TiXmlElement* current_el_2;
	while (current_el != NULL) {
		if (current_el->ValueTStr() == "BEWEGING") {
			current_el_2 = current_el->FirstChildElement();
			while (current_el_2 != NULL) {
				if (current_el_2->ValueTStr() != "SPELERNAAM"
						&& current_el_2->ValueTStr() != "RICHTING") {
					std::cerr << "Error: tag " << current_el->Value() << " not defined.\n";
				}
				current_el_2 = current_el_2->NextSiblingElement();
			}
			std::string dir_s = readElement(current_el, "RICHTING");
			std::string player_name = readElement(current_el, "SPELERNAAM");
			
			Direction dir = toDirection(dir_s);
			if (dir == Direction::no_dir) {
				std::cerr << "Invalid direction specified, skipping movement in movement file.\n";
				continue;
			}
			
			if (_players.find(player_name) == _players.end()) {
				std::cerr << "Invalid player specified, skipping movement in movement file.\n";
				continue;
			}
			
			_movements.push_back(Movement(dir, _players[player_name]));

			//std::cout << _movements.back().get_dir() << "\n";
		} else {
			std::cerr << "Error: tag " << current_el->Value() << " not defined.\n";
		}
		current_el = current_el->NextSiblingElement();
	}

	_initCheck = this;
	ENSURE(properlyInitialized(), "Constructor of Game did not end properly.");
}

bool Game::properlyInitialized() const {
	return _initCheck == this;
}

bool Game::reqElement(TiXmlElement* elem, const char* tag) {
	TiXmlElement* e = elem->FirstChildElement(tag);
	if (e == NULL) {
		return false;
	}
	return true;
}

void Game::parsePlayer(TiXmlElement* elem) {
	TiXmlElement* current_el = elem->FirstChildElement();
	std::string name;
	REQUIRE(reqElement(elem, "NAAM"), "Player must have a name specified.");
	while (current_el != NULL) {
		if (current_el->ValueTStr() == "NAAM") {
			name = readElement(current_el);
		} else {
			std::cerr << "Error: Tag " << current_el->Value() << " not defined.\n";
		}

		current_el = current_el->NextSiblingElement();
	}
	unsigned int x, y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		std::cerr << "Invalid x or y specified for player, skipping.\n";
		return;
	}
	
	if (_board.valid_location(x,y)) {
		std::cerr << "Invalid location given.\n";
		return;
	}
	
	Player* player = new Player(name, x, y);
	_players[name] = player;

	// Put on board
	// TODO Check consistency of playing board!

	_board(x, y) = player;

	//std::cout << _players[name].get_name() << std::endl;
}

void Game::parseObstacle(TiXmlElement* elem) {
	TiXmlElement* current_el = elem->FirstChildElement();
	std::string type;
	if (!reqElement(elem, "TYPE")) {
		std::cerr << "Obstacle must have a type specified.\n";
		return;
	}
	while (current_el != NULL) {
		if (current_el->ValueTStr() == "TYPE") {
			type = readElement(current_el);
		} else {
			std::cerr << "Error: tag " << current_el->Value() << " not defined.\n";
		}

		current_el = current_el->NextSiblingElement();
	}
	
	unsigned int x,y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		std::cerr << "Invalid x or y specified for obstacle, skipping.\n";
	}
	
	
	if (_board.valid_location(x,y)) {
		std::cerr << "Invalid location given.\n";
		return;
	}

	Thing* obst;
	if (type == "ton") {
		if (readAttribute(elem, "beweegbaar") != "true") {
			std::cerr << "Error: A barrel must be declared movable.\n";
		} else {
			obst = new Barrel(x, y);
			// Put on board
			_board(x, y) = obst;
		}
	} else if (type == "muur") {
		if (readAttribute(elem, "beweegbaar") != "false") {
			std::cerr << "Error: A wall may not be declared movable.\n";
		} else {
			obst = new Wall(x, y);
			// Put on board
			_board(x, y) = obst;
		}
	} else {
		std::cerr << "Error: Type " << type << " is not defined as an obstacle.\n";
	}
	
	//std::cout << _board(x,y)->is_movable() << "\n";
}

void Game::forceLowerCase(TiXmlElement* elem) {

	// This function loops through all "first" elements of the xml-file. Therefore elements like type or playername or not yet converted.
	// I don't know how to fix this yet though.

	TiXmlNode* child = 0;
	while (child = elem->IterateChildren(child)) {
		std::string data = child->Value();
		std::transform(data.begin(), data.end(), data.begin(), ::tolower);
		const char * data2 = data.c_str();
		child->SetValue(data2);
		//std::cout << child->Value() << std::endl;
	}
	return;
}

std::string Game::readElement(TiXmlElement* elem, const char* tag) {
	TiXmlElement* e = elem->FirstChildElement(tag);
	if (e == NULL) {
		std::cerr << "Error: Tag not defined.";
	}
	TiXmlNode* node = e->FirstChild();
	TiXmlText* text = node->ToText();
	return text->Value();
}

std::string Game::readElement(TiXmlElement* elem) {
	if (elem == NULL) {
		std::cerr << "Error: Tag not defined.";
	}
	TiXmlNode* node = elem->FirstChild();
	TiXmlText* text = node->ToText();
	return text->Value();
}

std::string Game::readAttribute(TiXmlElement* elem, const char* tag) {
	return std::string(elem->Attribute(tag));
}

void Game::writeBoard(std::ostream& stream) {
	/*Het huidige speelveld is Level 1:
	Eigenschappen van dit veld:
	-Breedte 10
	-Lengte 10*/

	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling writeBoard");

	stream << "Het huidige speelveld is " << _board.get_name() << ":\n"
			<< "Eigenschappen van dit veld:\n"
			<< "-Breedte " << _board.get_width() << "\n"
			<< "-Lengte " << _board.get_height() << "\n\n";

	// Find player.
	for (unsigned int i = 0; i != _board.get_width(); i++) {
		for (unsigned int j = 0; j != _board.get_height(); j++) {
			if (_board(i,j) != NULL && _board(i,j)->is_movable() == true) {
				stream << *_board(i,j) << "(" << i << "," << j <<").\n";
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
	//out << "popped\n";
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
	out << movement << std::endl;
	//std::cout << _board(x,y)->is_movable() << "\n";
	
	if (! _board.valid_location(x,y)) {
		std::cerr << "Not a valid location. Skipping movement.\n";
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
			std::cerr << "Can't move infinite weight (like a wall), skipping this movement.\n";
			return;
		}
		total_weight += _board(x_next, y_next)->get_weight();
		doDirection(movement.get_dir(), x_next, y_next);
	}
	
	if (_board.valid_location(x_next, y_next) and _board(x_next, y_next) != nullptr) {
		std::cerr << "Player (and perhaps other things) have no place to go. Skipping this movement.\n";
		return;
	}
		
	if (total_weight > movement.get_player()->get_maximum_weight()) {
		std::cerr << "Player tries to move too much weight. Skipping this movement.\n";
		return;
	}
	
	// move all things, we work backwards
	unsigned int x_new = x_next;
	unsigned int y_new = y_next;
	doReverseDirection(movement.get_dir(), x_new, y_new);
	while (x_next != x || y_next != y) {
		Thing* temp = _board(x_new, y_new);
		_board(x_new, y_new) = _board(x_next, y_next);
		_board(x_next, y_next) = temp;
		x_next = x_new;
		y_next = y_new;
		doReverseDirection(movement.get_dir(), x_new, y_new);
	}
	doDirection(movement.get_dir(), x, y);
	movement.get_player()->set_x(x);
	movement.get_player()->set_y(y);
	ENSURE(x_original != x || y_original != y, "Movement not completed, location remained the same.");
}

void Game::doAllMoves(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Game wasn't initialized when calling doAllMoves");
	out << "About to do all " << _movements.size() << " movements.\n";
	out << _board << "\nStarting now:\n";
	
	while (! _movements.empty()) {
		popMove(out);
		out << _board << "\n";
	}

	ENSURE(get_movements().empty(), "Not all movements were executed.");
}
