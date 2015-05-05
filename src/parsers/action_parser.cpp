/*
 * action_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert!!!!
 */

#include "action_parser.h"
#include "../actions/actions.h"
#include "../actions/move.h"
#include "../actions/attack.h"
#include <string>
#include "../../DesignByContract.h"

Action_parser::Action_parser(std::ostream* stream, std::string filename):
		Parser(stream, filename) {}


std::list<Action*> Action_parser::parse_action(TiXmlElement* move_elem, Game* g) {
	std::list<Action*> mp;
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
					log("Tag not defined", current_el_2);
				}
				current_el_2 = current_el_2->NextSiblingElement();
			}
			std::string player_name = readElement(current_el, "ID");
			std::string dir_s = readElement(current_el, "RICHTING");
			//std::cout << dir_s << std::endl;
			//std::cout << player_name << std::endl;
			Direction dir (dir_s);
			if (dir.get_dir() == Direction::Dirk::no_dir) {
				log("Invalid direction specified", current_el);
				current_el = current_el->NextSiblingElement();
				continue;
			}
			if (g->get_actor(player_name) == nullptr) {
				log("Actor doesn't exist", current_el);
				current_el = current_el->NextSiblingElement();
				continue;
			}

			if (current_el->ValueTStr() == "BEWEGING") {
				//std::cout << "Parsing " << player_name << " move to " << dir_s << std::endl;
				Action* ap = new Move(g->get_actor(player_name), dir_s);
				mp.push_back(ap);
			} else if (current_el->ValueTStr() == "AANVAL") {
				//std::cout << "Parsing " << player_name << " attack to " << dir_s << std::endl;

				if (g->get_player(player_name) == nullptr) {
					log("error attack moet met player", current_el);
				}
				Action* ap = new Attack(g->get_player(player_name), dir_s);
				mp.push_back(ap);
			}
		} else {
			std::string s = current_el->Value();
			//print(s + " not defined.");
		}
		current_el = current_el->NextSiblingElement();
	}
	return mp;
}


