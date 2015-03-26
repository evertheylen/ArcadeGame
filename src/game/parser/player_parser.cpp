/*
 * player_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */
#include "player_parser.h"


Player Player_parser::parse_player(TiXmlElement& elem, Game::Playermap& _players, Board& _board) {
	TiXmlElement& root = elem;
	TiXmlElement* first_child = root.FirstChildElement();
	TiXmlElement* current_el = first_child->FirstChildElement();
	/*if (first_child == NULL) {
		out << "Error: Error while parsing obstacle, no first child. Skipping.\n";
		return;
	} TODO fix the out operator overloading and the return of no players??*/
	std::string name;
	/*if (!reqElement(first_child, "NAAM")) {
		out << "Error: Player must have a name specified. Skipping.\n";
		return;
	} TODO Same here. */

	while (current_el != NULL) {
		if (current_el->ValueTStr() == "NAAM") {
			name = readElement(current_el);
		} else {
			//out << "Error: Error: Tag " << current_el->Value() << " not defined.\n";
		}

		current_el = current_el->NextSiblingElement();
	}

	int x, y;
	try {
		x = std::stoi(readAttribute(first_child, "x"));
		y = std::stoi(readAttribute(first_child, "y"));
	} catch (std::invalid_argument& e) {
		//out << "Error: Invalid x or y specified for player, skipping.\n";
		//return;
	}

	if (! _board.valid_location(x,y)) {
		//out << "Error: Invalid location given. Skipping player.\n";
		//return;
	}

	if (_board(x,y) != nullptr) {
		//out << "Error: Specified location of player not empty. Skipping.\n";
		//return;
	}

	if (_players.find(name) != _players.end()) {
		//out << "Error: Player already exists. Skipping.\n";
		//return;
	}

	Player* player = new Player(name, x, y);
	_players[name] = player;

	// Put on board

	_board(x, y) = player;
}




