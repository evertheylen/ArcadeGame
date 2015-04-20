/*
 * thing_parser.h
 *
 *  Created on: 28 Mar 2015
 *      Author: stijn
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "parser.h"
#include "../board/board.h"
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

#ifndef _Thing_parser
#define _Thing_parser

class Thing_parser: public Parser {
public:
	Thing_parser(std::ostream* stream, std::string filename);

	Thing_parser() = default;
	
	Thing* parse_wall(TiXmlElement* elem, Board& _board);
	MovableThing* parse_barrel(TiXmlElement* elem, Board& _board);
	Thing* parse_water(TiXmlElement* elem, Board& _board);
	Thing* parse_button(TiXmlElement* elem, Board& _board, Game::Gatemap _gates);
	Thing* parse_goal(TiXmlElement* elem, Board& _board);
	Thing* parse_boobytrap(TiXmlElement* elem, Board& _board);
	Thing* parse_gate(TiXmlElement* elem, Board& _board, Game::Gatemap& _gates);
};

#endif /* _Thing_parser */

