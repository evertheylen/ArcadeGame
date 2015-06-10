/*
 * Entity_parser.cpp
 *
 *  Created on: 28 Mar 2015
 *      Author: stijn & evert
 */


#include "../game/board.h"
#include "../entities/barrel.h"
#include "../entities/wall.h"
#include "../entities/water.h"
#include "../entities/button.h"
#include "../entities/gate.h"
#include "../entities/goal.h"
#include "../entities/entity.h"
#include "../entities/actor.h"
#include "../entities/boobytrap.h"
#include "../game/game.h"
#include <iostream>
#include <string>
#include "entity_parser.h"
#include "actor_parser.h"

struct Result {
	int x;
	int y;
};

Entity_parser::Entity_parser(std::ostream* stream, std::string filename):
		Parser(stream, filename) {}

struct Result Entity_parser::parse_entity(TiXmlElement* elem, Board& _board) {
	struct Result result;
	try {
		result.x = std::stoi(readAttribute(elem, "x"));
		result.y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y for entity", elem);
	}

	if (! _board.valid_location(result.x, result.y)) {
		fatal("Invalid location on board for entity", elem);
	}
	return result;
}

Wall* Entity_parser::parse_wall(TiXmlElement* elem, Board& _board) {
	Wall* wall;

	struct Result r = parse_entity(elem, _board);

	if (elem->ValueTStr() == "MUUR") {
		if (readAttribute(elem, "beweegbaar") != "false") {
			fatal("Wall may not be declared movable", elem);
		} else {
			wall = new Wall(r.x, r.y);
		}
	} else {
		fatal("Wall must be MUUR", elem);
	}
	return wall;
}

Barrel* Entity_parser::parse_barrel(TiXmlElement* elem, Board& _board) {
	Barrel* barrel;

	struct Result r = parse_entity(elem, _board);
	if (elem->ValueTStr() == "TON") {
		if (readAttribute(elem, "beweegbaar") != "true") {
			fatal("Barrel must be movable", elem);
		} else {
			barrel = new Barrel(r.x, r.y);
		}
	} else {
		fatal("Barrel must be TON", elem);
	}
	return barrel;
}

Water* Entity_parser::parse_water(TiXmlElement* elem, Board& _board, Game* game) {
	Water* water;
	struct Result r = parse_entity(elem, _board);

	if (elem->ValueTStr() == "WATER") {
		if (readAttribute(elem, "beweegbaar") != "false") {
			fatal("Water may not be movable");
		} else {
			water = new Water(r.x, r.y);
			if (readAttribute(elem, "contained", "false") == "true" && elem->FirstChild() != nullptr) {
				if (elem->FirstChild()->ValueTStr() == "CONTAINED") {
					if (elem->FirstChild()->FirstChild() != nullptr) {
						std::string tag = elem->FirstChild()->FirstChild()->ValueTStr();
						TiXmlElement* elem2 = elem->FirstChild()->FirstChildElement();

						Entity* contained_e = nullptr;
						if (tag == "SPELER") {
							Actor_parser ap;
							contained_e = ap.parse_player(elem2, _board);
						} else if (tag == "MONSTER") {
							Actor_parser ap;
							contained_e = ap.parse_monster(elem2, _board);
						} else if (tag == "TON") {
							Entity_parser ep;
							contained_e = ep.parse_barrel(elem2, _board);
						} else if (tag == "VALSTRIK") {
							Entity_parser ep;
							contained_e = ep.parse_boobytrap(elem2, _board);
						} else if (tag == "KNOP") {
							Entity_parser ep;
							contained_e = ep.parse_button(elem2, _board, game);
						} else if (tag == "POORT") {
							Entity_parser ep;
							contained_e = ep.parse_gate(elem2, _board);
						} else if (tag == "DOEL") {
							Entity_parser ep;
							contained_e = ep.parse_goal(elem2, _board);
						} else if (tag == "MUUR") {
							Entity_parser ep;
							contained_e = ep.parse_wall(elem2, _board);
						} else if (tag == "WATER") {
							Entity_parser ep;
							contained_e = ep.parse_water(elem2, _board, game);
						} else {
							log("Nothing was contained inside of this water");
						}
						water->contained = contained_e;
					}
				} else {
					fatal("Water can only have CONTAINED as child");
				}
			}
		}
	} else {
		fatal("Water must be WATER", elem);
	}
	return water;
}

Button* Entity_parser::parse_button(TiXmlElement* elem, Board& _board, Game* game) {
	Button* button;

	struct Result r = parse_entity(elem, _board);

	if (elem->ValueTStr() == "KNOP") {
		std::string id = readAttribute(elem, "id");
		Gate* g = _board.get_game()->get_gate(id);
		if (g == nullptr) {
			g = new Gate(r.x, r.y, id);
			Parser::dummyset++;
			game->add_gate(g);
			//log("Created a dummy gate.", elem);
			//fatal("Could not couple the button to the right gate.");
		}
		button = new Button(r.x, r.y , g);
	} else {
		fatal("Button must be KNOP", elem);
	}
	return button;
}


Gate* Entity_parser::parse_gate(TiXmlElement* elem, Board& _board) {
	Gate* gate;

	struct Result r = parse_entity(elem, _board);

	if (elem->ValueTStr() == "POORT") {
		if (readAttribute(elem, "beweegbaar") != "false")
			fatal("Gate may not be movable", elem);
		if (elem->FirstChildElement("ID") == nullptr)
			fatal("Tag ID not found", elem);
		if (std::string(elem->FirstChildElement("ID")->GetText()) == "")
			fatal("Name of gate cannot be empty", elem);
			
		std::string name = elem->FirstChildElement("ID")->GetText();
// 		log(std::string("name is ")+name, elem);
		gate = new Gate(r.x, r.y, name);

		if (readAttribute(elem, "open", "0") == "1") {
			gate->open();
		}

	} else {
		fatal("Gate must be POORT", elem);
	}
	return gate;
}

Goal* Entity_parser::parse_goal(TiXmlElement* elem, Board& _board) {
	Goal* goal;

	struct Result r = parse_entity(elem, _board);

	if (elem->ValueTStr() == "DOEL") {
		goal = new Goal(r.x, r.y);
	} else {
		fatal("Goal must be DOEL", elem);
	}
	return goal;
}

Boobytrap* Entity_parser::parse_boobytrap(TiXmlElement* elem, Board& _board) {
	Boobytrap* boobytrap;

	struct Result r = parse_entity(elem, _board);
	
	if (elem->ValueTStr() == "VALSTRIK") {
		boobytrap = new Boobytrap(r.x, r.y);
	} else {
		fatal("Boobytrap must be VALSTRIK", elem);
	}
	return boobytrap;
}
