/*
 * movement_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "movement_parser.h"
#include <string>
#include "../../DesignByContract.h"

Movement_parser::Movement_parser(std::ostream* stream, std::string filename):
		Parser(stream, filename) {}


std::list<Movement>* Movement_parser::parse_movement(TiXmlElement* move_elem, Game::Playermap& _players) {
	// NOTE hier heb ik de nieuwe log() en fatal() nog niet gebruikt, omdat deze toch sterk zal moeten herschreven worden
	std::list<Movement>* mp = new std::list<Movement>;
	REQUIRE(move_elem != NULL, "Failed to load movements file: No root element.");
	REQUIRE(move_elem->ValueTStr() == "BEWEGINGEN" || move_elem->ValueTStr() == "ACTIES", "Failed to load movements file: Wrong root element tag.");

	TiXmlElement* current_el = move_elem->FirstChildElement();

	current_el = move_elem->FirstChildElement();
	TiXmlElement* current_el_2;
	while (current_el != NULL) {
		if (current_el->ValueTStr() == "BEWEGING" || current_el->ValueTStr() == "AANVAL") {
			current_el_2 = current_el->FirstChildElement();
			while (current_el_2 != NULL) {
				if (current_el_2->ValueTStr() != "ID"
						&& current_el_2->ValueTStr() != "RICHTING") {
					std::string s = current_el->Value();
					//print(s + " not defined.");
				}
				current_el_2 = current_el_2->NextSiblingElement();
			}
			std::string player_name = readElement(current_el, "ID");
			std::string dir_s = readElement(current_el, "RICHTING");
			//std::cout << dir_s << std::endl;
			//std::cout << player_name << std::endl;
			Direction dir = toDirection(dir_s);
			if (dir == Direction::no_dir) {
				//print("Invalid direction specified, skipping movement in movement file.");
				current_el = current_el->NextSiblingElement();
				continue;
			}

			if (_players.find(player_name) == _players.end()) {
				//print("Invalid player specified, skipping movement in movement file.");
				current_el = current_el->NextSiblingElement();
				continue;
			}
			if (current_el->ValueTStr() == "BEWEGING") {
				mp->push_back(Movement(dir, _players[player_name]));
			} else {
				// TODO Push on attack, TODO Make attack class;
			}
		} else {
			std::string s = current_el->Value();
			//print(s + " not defined.");
		}
		current_el = current_el->NextSiblingElement();
	}
	return mp;
}


