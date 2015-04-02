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

#ifndef _Thing_parser
#define _Thing_parser

class Thing_parser: public Parser {
public:
	Wall parse_wall(TiXmlElement* elem, Board& _board);
	Barrel parse_barrel(TiXmlElement* elem, Board& _board);
	Water parse_water(TiXmlElement* elem, Board& _board);
	Button parse_button(TiXmlElement* elem, Board& _board);
	Goal parse_goal(TiXmlElement* elem, Board& _board);
	Boobytrap parse_boobytrap(TiXmlElement* elem, Board& _board);
	Gate parse_gate(TiXmlElement* elem, Board& _board, Game::Gatemap& _gates);
};

#endif /* _Thing_parser */

