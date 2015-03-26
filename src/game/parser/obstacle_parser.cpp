/*
 * obstacle_parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "obstacle_parser.h"
#include "../board/barrel.h"
#include "../board/wall.h"

Obstacle Obstacle_parser::parse_obstacle(TiXmlElement& elem, Board& _board) {
	TiXmlElement* current_el = elem.FirstChildElement();
	if (&elem == NULL) {
		//out << "Error: Error while parsing obstacle, no first child. Skipping.\n";
		//return;
	}

	std::string type;
	if (!reqElement(&elem, "TYPE")) {
		//out << "Error: Obstacle must have a type specified.\n";
		//return;
	}

	while (current_el != NULL) {
		if (current_el->ValueTStr() == "TYPE") {
			type = readElement(current_el);
		} else {
			//out << "Error: Error: tag " << current_el->Value() << " not defined.\n";
		}

		current_el = current_el->NextSiblingElement();
	}

	int x,y;
	/*try {
		x = std::stoi(readAttribute(&elem, "x"));
		y = std::stoi(readAttribute(&elem, "y"));
	} catch (std::invalid_argument& e) {
		out << "Error: Invalid x or y specified for obstacle, skipping.\n";
		//return;
	}*/

	if (! _board.valid_location(x,y)) {
		//out << "Error: Invalid location given. Skipping obstacle.\n";
		//return;
	}

	if (_board(x,y) != nullptr) {
		//out << "Error: Specified location of obstacle not empty. Skipping.\n";
		//return;
	}

	Thing* obst;
	if (type == "ton") {
		if (readAttribute(&elem, "beweegbaar") != "true") {
			//out << "Error: Error: A barrel must be declared movable.\n";
		} else {
			obst = new Barrel(x, y);
			// Put on board
			_board(x, y) = obst;
		}
	} else if (type == "muur") {
		if (readAttribute(&elem, "beweegbaar") != "false") {
			//out << "Error: Error: A wall may not be declared movable.\n";
		} else {
			obst = new Wall(x, y);
			// Put on board
			_board(x, y) = obst;
		}
	} else {
		//out << "Error: Error: Type " << type << " is not defined as an obstacle.\n";
	}
}

