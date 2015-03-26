/*
 * movement_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "movement_parser.h"
#include <string>
#include "../../DesignByContract.h"


std::list<Movement> Movement_parser::parse_movement(TiXmlElement& move_elem, Game::Playermap& _players) {
	// ---- Movements ----
	std::list<Movement> _movements;
	TiXmlElement* root = move_elem.FirstChildElement();
	REQUIRE(root != NULL, "Failed to load movements file: No root element.");
	REQUIRE(root->ValueTStr() == "BEWEGINGEN", "Failed to load movements file: Wrong root element tag.");

	TiXmlElement* current_el = root->FirstChildElement();

	current_el = root->FirstChildElement();
	TiXmlElement* current_el_2;
	while (current_el != NULL) {
		if (current_el->ValueTStr() == "BEWEGING") {
			current_el_2 = current_el->FirstChildElement();
			while (current_el_2 != NULL) {
				if (current_el_2->ValueTStr() != "SPELERNAAM"
						&& current_el_2->ValueTStr() != "RICHTING") {
					std::string s = current_el->Value();
					print(s + " not defined.");
				}
				current_el_2 = current_el_2->NextSiblingElement();
			}
			std::string dir_s = readElement(current_el, "RICHTING");
			std::string player_name = readElement(current_el, "SPELERNAAM");

			Direction dir = toDirection(dir_s);
			if (dir == Direction::no_dir) {
				print("Invalid direction specified, skipping movement in movement file.");
				current_el = current_el->NextSiblingElement();
				continue;
			}

			if (_players.find(player_name) == _players.end()) {
				print("Invalid player specified, skipping movement in movement file.");
				current_el = current_el->NextSiblingElement();
				continue;
			}

			_movements.push_back(Movement(dir, _players[player_name]));
		} else {
			std::string s = current_el->Value();
			print(s + " not defined.");
		}
		current_el = current_el->NextSiblingElement();
	}
	return _movements;
}

