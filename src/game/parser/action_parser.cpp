/*
 * action_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert!!!!
 */

#include "action_parser.h"
#include <string>
#include "../../DesignByContract.h"

Action_parser::Action_parser(std::ostream* stream, std::string filename):
		Parser(stream, filename) {}


std::list<Action>* Action_parser::parse_action(TiXmlElement* move_elem, Game::Playermap& _players) {
	// NOTE hier heb ik de nieuwe log() en fatal() nog niet gebruikt, omdat deze toch sterk zal moeten herschreven worden
	std::list<Action>* mp = new std::list<Action>;
	if(move_elem == nullptr) fatal("Failed to load actions file: No root element.");
	if(move_elem->ValueTStr() != "BEWEGINGEN" && move_elem->ValueTStr() != "ACTIES") fatal("Failed to load actions file: Wrong root element tag.");

	TiXmlElement* current_el = move_elem->FirstChildElement();

	current_el = move_elem->FirstChildElement();
	TiXmlElement* current_el_2;
	while (current_el != nullptr) {
		if (current_el->ValueTStr() == "BEWEGING" || current_el->ValueTStr() == "AANVAL") {
			current_el_2 = current_el->FirstChildElement();
			while (current_el_2 != nullptr) {
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
				//print("Invalid direction specified, skipping action in action file.");
				current_el = current_el->NextSiblingElement();
				continue;
			}

			if (_players.find(player_name) == _players.end()) {
				//print("Invalid player specified, skipping action in action file.");
				current_el = current_el->NextSiblingElement();
				continue;
			}
			if (current_el->ValueTStr() == "BEWEGING") {
				mp->push_back(Action(dir, _players[player_name]));
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


