/*
 * obstacle_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../board/obstacle.h"
#include "parser.h"
#include "../board/board.h"

#ifndef _Obstacle_parser
#define _Obstacle_parser

class Obstacle_parser: public Parser {
public:
	Obstacle parse_obstacle(TiXmlElement* elem, Board& _board);
};

#endif /* _Obstacle_parser */
