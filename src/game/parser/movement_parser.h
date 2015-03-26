/*
 * movement_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../movement/movement.h"
#include "parser.h"
#include "../game.h"

#include <list>

#ifndef _Movement_parser
#define _Movement_parser

class Movement_parser: public Parser {
public:
	std::list<Movement> parse_movement(TiXmlElement& move_elem, Game::Playermap& _players);
};

#endif /* _Movement_parser */
