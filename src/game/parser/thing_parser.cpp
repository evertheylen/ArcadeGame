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
#include <string>


Thing* Thing_parser::parse_wall(TiXmlElement* elem, Board& _board) {
	int x,y;
	//try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	/*} catch (std::invalid_argument& e) {
		out << "Error: Invalid x or y specified for obstacle, skipping.\n";
		//return;
	}*/ // TODO FIX THE ERRORS PLS

	if (! _board.valid_location(x,y)) {
		//out << "Error: Invalid location given. Skipping obstacle.\n";
		//return;
	}

	Wall* wall;

	if (elem->ValueTStr() == "MUUR") {
		if (readAttribute(elem, "beweegbaar") != "false") {
			//out << "Error: Error: A wall may not be declared movable.\n";
		} else {
			wall = new Wall(x, y);
			// Put on board
			//_board(x, y) = obst;
		}
	} else {
			//out << "Error: Error: Type " << type << " is not defined as an obstacle.\n";
	}
	return wall;
}

MovableThing* Thing_parser::parse_barrel(TiXmlElement* elem, Board& _board) {
	int x,y;
	//try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	/*} catch (std::invalid_argument& e) {
		out << "Error: Invalid x or y specified for obstacle, skipping.\n";
		//return;
	}*/ // TODO FIX THE ERRORS PLS

	if (! _board.valid_location(x,y)) {
		//out << "Error: Invalid location given. Skipping obstacle.\n";
		//return;
	}

	Barrel* barrel;
	if (elem->ValueTStr() == "TON") {
		if (readAttribute(elem, "beweegbaar") != "true") {
			//out << "Error: Error: A barrel must be declared movable.\n";
		} else {
			barrel = new Barrel(x, y);
			// Put on board
			//_board(x, y) = obst;
		}
	} else {
		//out << "Error: Error: Type " << type << " is not defined as an obstacle.\n";
	}
	return barrel;
}

Thing* Thing_parser::parse_water(TiXmlElement* elem, Board& _board) {
	int x,y;
	//try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	/*} catch (std::invalid_argument& e) {
		out << "Error: Invalid x or y specified for obstacle, skipping.\n";
		//return;
	}*/ // TODO FIX THE ERRORS PLS

	if (! _board.valid_location(x,y)) {
		//out << "Error: Invalid location given. Skipping obstacle.\n";
		//return;
	}

	Water* water;
	if (elem->ValueTStr() == "WATER") {
		if (readAttribute(elem, "beweegbaar") != "false") {
			//out << "Error: Error: A wall may not be declared movable.\n";
		} else {
			water = new Water(x, y);
			// Put on board
			//_board(x, y) = obst;
		}
	} else {
		//out << "Error: Error: Type " << type << " is not defined as an obstacle.\n";
	}
	return water;
}

Thing* Thing_parser::parse_button(TiXmlElement* elem, Board& _board, Game::Gatemap _gates) {
	int x,y;
	//try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	/*} catch (std::invalid_argument& e) {
		out << "Error: Invalid x or y specified for obstacle, skipping.\n";
		//return;
	}*/ // TODO FIX THE ERRORS PLS

	if (! _board.valid_location(x,y)) {
		//out << "Error: Invalid location given. Skipping obstacle.\n";
		//return;
	}

	Button* button;
	if (elem->ValueTStr() == "KNOP") {
		std::string id = readAttribute(elem, "id");
		if (_gates.find(id) == _gates.end()) {
			//TODO ERRRRREUR
		}
		button = new Button(x, y , _gates[id]);
		//button = new Button()
	} else {
		//out << "Error: Error: Type " << type << " is not defined as an obstacle.\n";
	}
	return button;
}

Thing* Thing_parser::parse_goal(TiXmlElement* elem, Board& _board) {
	int x,y;
	//try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	/*} catch (std::invalid_argument& e) {
		out << "Error: Invalid x or y specified for obstacle, skipping.\n";
		//return;
	}*/ // TODO FIX THE ERRORS PLS

	if (! _board.valid_location(x,y)) {
		//out << "Error: Invalid location given. Skipping obstacle.\n";
		//return;
	}

	Goal* goal;
	if (elem->ValueTStr() == "DOEL") {
		goal = new Goal(x, y);
	} else {
		//out << "Error: Error: Type " << type << " is not defined as an obstacle.\n";
	}
	return goal;
}

Thing* Thing_parser::parse_boobytrap(TiXmlElement* elem, Board& _board) {
	int x,y;
	//try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	/*} catch (std::invalid_argument& e) {
		out << "Error: Invalid x or y specified for obstacle, skipping.\n";
		//return;
	}*/ // TODO FIX THE ERRORS PLS

	if (! _board.valid_location(x,y)) {
		//out << "Error: Invalid location given. Skipping obstacle.\n";
		//return;
	}

	Boobytrap* boobytrap;
	if (elem->ValueTStr() == "VALSTRIK") {
		boobytrap = new Boobytrap(x, y);
	} else {
		//out << "Error: Error: Type " << type << " is not defined as an obstacle.\n";
	}
	return boobytrap;
}

Thing* Thing_parser::parse_gate(TiXmlElement* elem, Board& _board, Game::Gatemap& _gates) {
	int x,y;
	//try {
		x = std::stoi(readAttribute(elem, "x"));
		y = std::stoi(readAttribute(elem, "y"));
	/*} catch (std::invalid_argument& e) {
		out << "Error: Invalid x or y specified for obstacle, skipping.\n";
		//return;
	}*/ // TODO FIX THE ERRORS PLS

	if (! _board.valid_location(x,y)) {
		//out << "Error: Invalid location given. Skipping obstacle.\n";
		//return;
	}

	Gate* gate;
	if (elem->ValueTStr() == "POORT") {
		if (readAttribute(elem, "beweegbaar") != "false") {
			//out << "Error: Error: A wall may not be declared movable.\n";
		} else if (elem->FirstChildElement("ID") != NULL) {
			std::string name = elem->FirstChildElement("ID")->Value();
			gate = new Gate(x,y);
			_gates[name] = gate;

			// TODO Fix the copy problem with gatemap and playermap!!!!

		} else {
			// ERRROOOOOOOOOR TODO
		}
	} else {
		//out << "Error: Error: Type " << type << " is not defined as an obstacle.\n";
	}
	return gate;
}

