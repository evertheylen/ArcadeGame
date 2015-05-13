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


std::list<Action*> Action_parser::parse_actions(TiXmlElement* move_elem, Game* g) {
	std::list<Action*> mp;
	if(move_elem == nullptr) fatal("Failed to load actions file: No root element.");
	if(move_elem->ValueTStr() != "BEWEGINGEN" && move_elem->ValueTStr() != "ACTIES") fatal("Failed to load actions file: Wrong root element tag.");

	TiXmlElement* current_el = move_elem->FirstChildElement();

	current_el = move_elem->FirstChildElement();
	while (current_el != nullptr) {
		Action* a;
		try {
			a = parse_action(current_el, g);
			mp.push_back(a);
		} catch (ParseError& e) {
			log(std::string("Error in parse_actions: ") + e.what(), current_el);
			continue;
		}
		current_el = current_el->NextSiblingElement();
	}
	return mp;
}

Action* Action_parser::parse_action(TiXmlElement* current_el, Game* g) {
	Action* a;
	if (current_el == nullptr) {
		fatal("current_el is nullptr");
	}
	
	if (current_el->ValueTStr() == "BEWEGING" || current_el->ValueTStr() == "AANVAL") {
		TiXmlElement* current_el_2 = current_el->FirstChildElement();
		while (current_el_2 != nullptr) {
			if (current_el_2->ValueTStr() != "ID"
					&& current_el_2->ValueTStr() != "RICHTING") {
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
			fatal("Invalid direction specified", current_el);
			current_el = current_el->NextSiblingElement();
		}
		if (g->get_actor(player_name) == nullptr) {
			fatal("Actor doesn't exist", current_el);
			current_el = current_el->NextSiblingElement();
		}

		if (current_el->ValueTStr() == "BEWEGING") {
			//std::cout << "Parsing " << player_name << " move to " << dir_s << std::endl;
			a = new Move(g->get_actor(player_name), dir_s);
		} else if (current_el->ValueTStr() == "AANVAL") {
			//std::cout << "Parsing " << player_name << " attack to " << dir_s << std::endl;

			if (g->get_player(player_name) == nullptr) {
				fatal("error attack moet met player", current_el);
			}
			a = new Attack(g->get_player(player_name), dir_s);
		}
		std::cout << "action in dir: " << dir_s << "\n";
	} else {
		std::string s = current_el->Value();
		fatal(s + " not defined.", current_el);
	}
	return a;
}

