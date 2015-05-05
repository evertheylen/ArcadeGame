/*
 * Entity_parser.h
 *
 *  Created on: 28 Mar 2015
 *      Author: stijn
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "parser.h"
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

#ifndef _Entity_parser
#define _Entity_parser

class Entity_parser: public Parser {
public:
	Entity_parser(std::ostream* stream, std::string filename);

	Entity_parser() = default;
	
	Wall* parse_wall(TiXmlElement* elem, Board& _board);
	Barrel* parse_barrel(TiXmlElement* elem, Board& _board);
	Water* parse_water(TiXmlElement* elem, Board& _board);
	Button* parse_button(TiXmlElement* elem, Board& _board);
	Goal* parse_goal(TiXmlElement* elem, Board& _board);
	Boobytrap* parse_boobytrap(TiXmlElement* elem, Board& _board);
	Gate* parse_gate(TiXmlElement* elem, Board& _board);
};

#endif /* _Entity_parser */

