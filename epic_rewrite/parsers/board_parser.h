/*
 * board_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../game/board.h"
#include "../game/game.h"
#include "actor_parser.h"
#include "parser.h"
#include "entity_parser.h"

#ifndef _Board_parser
#define _Board_parser

class Board_parser: public Parser {
public:
	Board_parser(std::ostream* stream, std::string filename);
	
	Board_parser() = default;
	
	Board* parse_board(TiXmlElement* board_elem, Game::Playermap& _players, Game::Gatemap& _gates);
};

#endif /* _Board_parser */
