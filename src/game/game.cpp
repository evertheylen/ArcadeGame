#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "../../lib/tinyxml/tinyxml.h"
#include "game.h"
#include "../DesignByContract.h"
#include "board/barrel.h"
#include "board/wall.h"
#include "movement/movement.h"

Game::Game(TiXmlDocument& board_doc, TiXmlDocument& moves_doc) {
	TiXmlElement* root = board_doc.FirstChildElement();
	if (root == NULL) {
		std::cerr << "Failed to load board file: No root element." << std::endl;
		board_doc.Clear();
		return;
		// TODO proper error handling, also below
	}

	TiXmlElement* current_el = root->FirstChildElement();
	std::string boardname;
	_players = Playermap();

	int x = atoi(readElement(root, "BREEDTE").c_str());
	int y = atoi(readElement(root, "LENGTE").c_str());

	_board = Board(x, y);

	//TODO Test if all necessary elements are specified in the xml file. Else error!

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
						std::cerr << "Error: tag " << current_el->Value()
								<< " not defined." << std::endl;
						//TODO proper error handling!
					}
				}
			}
		}
		current_el = current_el->NextSiblingElement();
	}

	// Load Board properties
	/*boardname = readElement(root, "NAAM");
	 x = atoi(readElement(root, "BREEDTE").c_str());
	 y = atoi(readElement(root, "LENGTE").c_str());
	 */
	// TODO Check on error atoi. If it returns 0 -> error.
	std::cout << "Width: " << _board.get_width() << "   Height: "
			<< _board.get_height() << "   Name: " << _board.get_name()
			<< std::endl;

	// Load players

	/*for (TiXmlElement* player_el = root->FirstChildElement("SPELER");
	 player_el != NULL;
	 player_el = player_el->NextSiblingElement("SPELER")) {
	 std::string name = readElement(player_el, "NAAM");
	 unsigned int x = atoi(readAttribute(player_el, "x").c_str());
	 unsigned int y = atoi(readAttribute(player_el, "y").c_str());
	 Player* player = new Player(name, x, y);
	 _players[name] = *player;

	 // Put on board
	 _board(x,y) = player;

	 std::cout << _players[name].get_name() << std::endl;
	 }*/

	// Obstacles
	/*
	 for (TiXmlElement* obstacle_el = root->FirstChildElement("OBSTAKEL");
	 obstacle_el != NULL;
	 obstacle_el = obstacle_el->NextSiblingElement("OBSTAKEL")) {
	 std::string type = readElement(obstacle_el, "TYPE");
	 unsigned int x = atoi(readAttribute(obstacle_el, "x").c_str());
	 unsigned int y = atoi(readAttribute(obstacle_el, "y").c_str());

	 Thing* obst;
	 if (type == "ton") {
	 // TODO check beweegbaar
	 obst = new Barrel(x,y);
	 } else if (type == "muur") {
	 // TODO check beweegbaar
	 obst = new Wall(x,y);
	 }

	 // Put on board
	 _board(x,y) = obst;

	 std::cout << _board(x,y)->is_movable() << "\n";
	 }*/

	// Movements
	root = moves_doc.FirstChildElement();
	if (root == NULL) {
		std::cerr << "Failed to load movements file: No root element."
				<< std::endl;
		moves_doc.Clear();
		return;
	}
	current_el = root->FirstChildElement();
	TiXmlElement* current_el_2;
	while (current_el != NULL) {
		if (current_el->ValueTStr() == "BEWEGING") {
			current_el_2 = current_el->FirstChildElement();
			while (current_el_2 != NULL) {
				if (current_el_2->ValueTStr() != "SPELERNAAM"
						&& current_el_2->ValueTStr() != "RICHTING") {
					std::cerr << "Error: tag " << current_el->Value()
							<< " not defined." << std::endl;
					//TODO proper error handling!
				}
				current_el_2 = current_el_2->NextSiblingElement();
			}
			std::string dir_s = readElement(current_el, "RICHTING");
			std::string player_name = readElement(current_el, "SPELERNAAM");

			Movement move(dir_s, _players[player_name]);
			_movements.push_back(move);

			//std::cout << _movements.back().get_dir() << "\n";
		} else {
			std::cerr << "Error: tag " << current_el->Value() << " not defined."
					<< std::endl;
			//TODO proper error handling!
		}
		current_el = current_el->NextSiblingElement();
	}
	/*
	 std::cout << "Starting..\n";
	 for (TiXmlElement* move_el = root->FirstChildElement("BEWEGING");
	 move_el != NULL;
	 move_el = move_el->NextSiblingElement("BEWEGING")) {
	 std::string dir_s = readElement(move_el, "RICHTING");
	 std::string player_name = readElement(move_el, "SPELERNAAM");

	 Movement move(dir_s, &_players[player_name]);
	 _movements.push_back(move);

	 std::cout << _movements.back().get_dir() << "\n";
	 }*/
}

void Game::parsePlayer(TiXmlElement* elem) {
	TiXmlElement* current_el = elem->FirstChildElement();
	std::string name;
	//TODO Test if name is specified!
	while (current_el != NULL) {
		if (current_el->ValueTStr() == "NAAM") {
			name = readElement(current_el);
		} else {
			std::cerr << "Error: tag " << current_el->Value() << " not defined."
					<< std::endl;
		}

		current_el = current_el->NextSiblingElement();
	}
	unsigned int x = atoi(readAttribute(elem, "x").c_str());
	unsigned int y = atoi(readAttribute(elem, "y").c_str());
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
	//TODO Test if type is specified!
	while (current_el != NULL) {
		if (current_el->ValueTStr() == "TYPE") {
			type = readElement(current_el);
		} else {
			std::cerr << "Error: tag " << current_el->Value() << " not defined."
					<< std::endl;
		}

		current_el = current_el->NextSiblingElement();
	}
	unsigned int x = atoi(readAttribute(elem, "x").c_str());
	unsigned int y = atoi(readAttribute(elem, "y").c_str());

	Thing* obst;
	if (type == "ton") {
		// TODO check beweegbaar
		obst = new Barrel(x, y);
	} else if (type == "muur") {
		// TODO check beweegbaar
		obst = new Wall(x, y);
	}
	
	// Put on board
	_board(x, y) = obst;

	//std::cout << _board(x,y)->is_movable() << "\n";
}

void Game::forceLowerCase(TiXmlElement* elem) {

	// TODO This function loops through all "first" elements of the xml-file. Therefore elements like type or playername or not yet converted.
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
	for (std::list<Movement>::iterator i = _movements.begin(); i != _movements.end(); i++) {
		stream << *i << std::endl;
	}
}

void Game::popMove() {
	// TODO Require length >= 1
	std::cout << "popped\n";
	doMove(_movements.front());
	_movements.pop_front();
}

void Game::doMove(Movement& movement) {
	// TODO check / require move obstacle.
	unsigned int x = movement.get_player()->get_x();
	unsigned int y = movement.get_player()->get_y();
	std::cout << movement << std::endl;
	//std::cout << _board(x,y)->is_movable() << "\n";
	
	REQUIRE(_board.valid_location(x,y), "Not a valid location.");
	
	// calculate total weight
	unsigned int x_next = x;
	unsigned int y_next = y;
	// calculate new location
	doDirection(movement.get_dir(), x_next, y_next);  // x or y are modified
	int total_weight = 0;
	// while not out of board and not an empty spot
	while (_board.valid_location(x_next, y_next) && _board(x_next, y_next) != nullptr) {
		REQUIRE(_board(x_next, y_next)->get_weight() != -1, "Can't move infinite weight (like a wall)");
		total_weight += _board(x_next, y_next)->get_weight();
		doDirection(movement.get_dir(), x_next, y_next);
	}
	REQUIRE(_board.valid_location(x_next, y_next) && _board(x_next, y_next) == nullptr, "Player (and perhaps other things) have no place to go.");
	REQUIRE(total_weight <= movement.get_player()->get_maximum_weight(), "Player tries to move too much weight.");
	
	// move all things, we work backwards
	unsigned int x_new = x_next;
	unsigned int y_new = y_next;
	doReverseDirection(movement.get_dir(), x_new, y_new);
	while (x_next != x || y_next != y) {
		#define print_status(obj)\
			if (obj==nullptr) {\
				std::cout << "is nullptr" << std::endl;\
			} else {\
				std::cout << "is of char " << obj->to_char() << std::endl;\
			}\
		
		Thing* temp = _board(x_new, y_new);
		std::cout << x_new << ", "<< y_new << ", "<< x_next << ", "<< y_next << ", " << std::endl;
		print_status(temp);
		_board(x_new, y_new) = _board(x_next, y_next);
		print_status(_board(x_new, y_new));
		_board(x_next, y_next) = temp;
		print_status(_board(x_next, y_next));
		x_next = x_new;
		y_next = y_new;
		doReverseDirection(movement.get_dir(), x_new, y_new);
	}
	doDirection(movement.get_dir(), x, y);
	movement.get_player()->set_x(x);
	movement.get_player()->set_y(y);
}

void Game::doAllMoves() {
	std::cout << "About to do all " << _movements.size() << " movements.\n";
	std::cout << _board << "\nStarting now:\n";
	
	while (! _movements.empty()) {
		doMove(_movements.front());
		_movements.pop_front();
		std::cout << _board << "\n";
	}
}
