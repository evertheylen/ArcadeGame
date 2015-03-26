/*
 * board_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../board/board.h"
#include "parser.h"
#include "player_parser.h"
#include "obstacle_parser.h"

#ifndef _Board_parser
#define _Board_parser

class Board_parser: public Parser {
public:
	Board parse_board(TiXmlElement& board_elem);
};

#endif /* _Board_parser */
