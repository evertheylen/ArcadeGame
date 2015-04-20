/*
 * thing_parser.cpp
 *
 *  Created on: 28 Mar 2015
 *      Author: stijn
 */

/*
 * obstacle_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "thing_parser.h"
#include "../board/barrel.h"
#include "../board/wall.h"
#include "../board/water.h"
#include "../board/button.h"
#include "../board/gate.h"
#include "../board/goal.h"
#include "../board/thing.h"
#include "../board/movable_thing.h"
#include "../board/living_thing.h"
#include "../board/boobytrap.h"
#include "../game.h"
#include <iostream>
#include <string>

Thing_parser::Thing_parser(std::ostream* stream, std::string filename):
		Parser(stream, filename) {}

Thing* Thing_parser::parse_wall(TiXmlElement* elem, Board& _board) {
	int x,y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y for wall", elem);
	}

	if (! _board.valid_location(x,y)) {
		fatal("Invalid location on board for wall", elem);
	}

	Wall* wall;

	if (elem->ValueTStr() == "MUUR") {
		if (readAttribute(elem, "beweegbaar") != "false") {
			fatal("Wall may not be declared movable", elem);
		} else {
			wall = new Wall(x, y);
		}
	} else {
		fatal("Wall must be MUUR", elem);
	}
	return wall;
}

MovableThing* Thing_parser::parse_barrel(TiXmlElement* elem, Board& _board) {
	int x,y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y for barrel", elem);
	}

	if (! _board.valid_location(x,y)) {
		fatal("Invalid location on board for barrel", elem);
	}

	Barrel* barrel;
	if (elem->ValueTStr() == "TON") {
		if (readAttribute(elem, "beweegbaar") != "true") {
			fatal("Barrel must be movable", elem);
		} else {
			barrel = new Barrel(x, y);
		}
	} else {
		fatal("Barrel must be TON", elem);
	}
	return barrel;
}

Thing* Thing_parser::parse_water(TiXmlElement* elem, Board& _board) {
	int x,y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y for water", elem);
	}

	if (! _board.valid_location(x,y)) {
		fatal("Invalid location on board for water", elem);
	}

	Water* water;
	if (elem->ValueTStr() == "WATER") {
		if (readAttribute(elem, "beweegbaar") != "false") {
			fatal("Water may not be movable");
		} else {
			water = new Water(x, y);
		}
	} else {
		fatal("Water must be WATER", elem);
	}
	return water;
}

Thing* Thing_parser::parse_button(TiXmlElement* elem, Board& _board, Game::Gatemap _gates) {
	int x,y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y for button", elem);
	}

	if (! _board.valid_location(x,y)) {
		fatal("Invalid location on board for button", elem);
	}

	Button* button;
	if (elem->ValueTStr() == "KNOP") {
		std::string id = readAttribute(elem, "id");
		/*for (auto s: _gates) {
			std::cout << "  " << s.first << ": " << s.second << "\n";
		}*/
		if (_gates.find(id) == _gates.end()) {
			fatal("Could not couple the button to the right gate.");
		}
		button = new Button(x, y , _gates[id]);
	} else {
		fatal("Button must be KNOP", elem);
	}
	return button;
}


Thing* Thing_parser::parse_gate(TiXmlElement* elem, Board& _board, Game::Gatemap& _gates) {
	int x,y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y for gate", elem);
	}

	if (! _board.valid_location(x,y)) {
		fatal("Invalid location on board for gate", elem);
	}

	Gate* gate;
	if (elem->ValueTStr() == "POORT") {
		if (readAttribute(elem, "beweegbaar") != "false")
			fatal("Gate may not be movable", elem);
		if (elem->FirstChildElement("ID") == nullptr)
			fatal("Tag ID not found", elem);
		if (std::string(elem->FirstChildElement("ID")->GetText()) == "")
			fatal("Name of gate cannot be empty", elem);
			
		std::string name = elem->FirstChildElement("ID")->GetText();
		//std::cout << "  name is " << name << "\n";
		gate = new Gate(x,y,name);
		_gates[name] = gate;

		// TODO Fix the copy problem with gatemap and playermap!!!
	} else {
		fatal("Gate must be POORT", elem);
	}
	return gate;
}

Thing* Thing_parser::parse_goal(TiXmlElement* elem, Board& _board) {
	int x,y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y for goal", elem);
	}

	if (! _board.valid_location(x,y)) {
		fatal("Invalid location on board for goal", elem);
	}

	Goal* goal;
	if (elem->ValueTStr() == "DOEL") {
		goal = new Goal(x, y);
	} else {
		fatal("Goal must be DOEL", elem);
	}
	return goal;
}

Thing* Thing_parser::parse_boobytrap(TiXmlElement* elem, Board& _board) {
	int x,y;
	try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	} catch (std::invalid_argument& e) {
		fatal("Invalid x or y for boobytrap", elem);
	}

	if (! _board.valid_location(x,y)) {
		fatal("Invalid location on board for boobytrap", elem);
	}
	// TODO Movable?
	
	Boobytrap* boobytrap;
	if (elem->ValueTStr() == "VALSTRIK") {
		boobytrap = new Boobytrap(x, y);
	} else {
		fatal("Boobytrap must be VALSTRIK", elem);
	}
	return boobytrap;
}
