/*
 * player_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../board/player.h"
#include "../board/board.h"
#include "parser.h"
#include "../game.h"

#ifndef _Player_parser
#define _Player_parser

class Player_parser: public Parser {
public:
	Player parse_player(TiXmlElement& elem, Game::Playermap& _players, Board& _board);
};
#endif /* _Player_parser */
