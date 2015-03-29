/*
 * player_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../board/player.h"
#include "../board/board.h"
#include "../board/monster.h"
#include "parser.h"
#include "../game.h"

#ifndef _Living_thing_parser
#define _Living_thing_parser

class Living_thing_parser: public Parser {
public:
	Player parse_player(TiXmlElement* elem, Game::Playermap& _players, Board& _board);
	Monster parse_monster(TiXmlElement* elem, Game::Playermap& _players, Board& _board);
};
#endif /* _Player_parser */
