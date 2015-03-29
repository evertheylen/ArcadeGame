/*
 * thing_parser.h
 *
 *  Created on: 28 Mar 2015
 *      Author: stijn
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../board/thing.h"
#include "parser.h"
#include "../board/board.h"

#ifndef _Thing_parser
#define _Thing_parser

class Thing_parser: public Parser {
public:
	Thing parse_thing(TiXmlElement* elem, Board& _board);
};

#endif /* _Thing_parser */

