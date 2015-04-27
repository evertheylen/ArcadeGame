/*
 * game_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../game/game.h"
#include "parser.h"
#include "board_parser.h"
#include <iostream>

#ifndef _game_parser
#define _game_parser

class Game_parser: public Parser {
public:
	Game_parser(std::ostream* stream, std::string filename);
	
	Game_parser() = default;
	
	Game* parse_game(TiXmlElement* board_elem, TiXmlElement* move_elem);
};

#endif /* _game_parser */
