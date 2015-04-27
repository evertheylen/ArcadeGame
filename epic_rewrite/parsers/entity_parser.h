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
#include "../game.h"
#include <iostream>
#include <string>

#ifndef _Entity_parser
#define _Entity_parser

class Entity_parser: public Parser {
public:
	Entity_parser(std::ostream* stream, std::string filename);

	Entity_parser() = default;
	
	Entity* parse_wall(TiXmlElement* elem, Board& _board);
	Entity* parse_barrel(TiXmlElement* elem, Board& _board);
	Entity* parse_water(TiXmlElement* elem, Board& _board);
	Entity* parse_button(TiXmlElement* elem, Board& _board, Game::Gatemap _gates);
	Entity* parse_goal(TiXmlElement* elem, Board& _board);
	Entity* parse_boobytrap(TiXmlElement* elem, Board& _board);
	Entity* parse_gate(TiXmlElement* elem, Board& _board, Game::Gatemap& _gates);
};

#endif /* _Entity_parser */

