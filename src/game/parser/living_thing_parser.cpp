/*
 * player_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */
#include "living_thing_parser.h"


Living_thing_parser::Living_thing_parser(std::ostream* stream, std::string filename): 
		Parser(stream, filename) {}

LivingThing* Living_thing_parser::parse_player(TiXmlElement* elem, Game::Playermap& _players, Board& _board) {
	TiXmlElement* current_el = elem->FirstChildElement();
	if (elem == nullptr) fatal("Elem was null", elem);
	std::string name;
	if (!reqElement(elem, "NAAM")) fatal("Player has no name specified", elem);

	while (current_el != NULL) {
		if (current_el->ValueTStr() == "NAAM") {
			name = readElement(current_el);
		} else {
			//out << "Error: Error: Tag " << current_el->Value() << " not defined.\n";
			log(std::string("tag ") + current_el->Value() + " not defined");
		}
		current_el = current_el->NextSiblingElement();
	}

	int x, y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y specified for player", elem);
	}

	if (! _board.valid_location(x,y)) {
		fatal("Invalid location for player", elem);
	}

	if (_players.find(name) != _players.end()) {
		fatal(std::string("Player with name \'") + name + "\' already exists", elem);
	}

	Player* player = new Player(name, x, y);
	_players[name] = player;

	return player;
}

LivingThing* Living_thing_parser::parse_monster(TiXmlElement* elem, Game::Playermap& _players, Board& _board) {
	TiXmlElement* current_el = elem->FirstChildElement();
	if (elem == nullptr) fatal("Elem was null", elem);
	std::string name;
	if (!reqElement(elem, "ID")) fatal("Monster has no ID specified", elem);

	while (current_el != NULL) {
		if (current_el->ValueTStr() == "ID") {
			name = readElement(current_el);
		} else {
			//out << "Error: Error: Tag " << current_el->Value() << " not defined.\n";
			log(std::string("tag ") + current_el->Value() + " not defined");
		}
		current_el = current_el->NextSiblingElement();
	}

	int x, y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y specified for monster", elem);
	}

	if (! _board.valid_location(x,y)) {
		fatal("Invalid location for monster", elem);
	}

	if (_players.find(name) != _players.end()) {
		fatal(std::string("Monster with name \'") + name + "\' already exists", elem);
	}

	Monster* monster = new Monster(name, x, y);
	_players[name] = monster;

	return monster;
}




