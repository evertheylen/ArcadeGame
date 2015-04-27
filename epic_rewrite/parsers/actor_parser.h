/*
 * player_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../entities/player.h"
#include "../game/board.h"
#include "../entities/monster.h"
#include "../entities/actor.h"
#include "parser.h"
#include "../game.h"

#ifndef _Actor_parser
#define _Actor_parser

class Actor_parser: public Parser {
public:
	Actor_parser(std::ostream* stream, std::string filename);
	
	Actor_parser() = default;

	Actor* parse_player(TiXmlElement* elem, Game::Playermap& _players, Board& _board);
	Actor* parse_monster(TiXmlElement* elem, Game::Playermap& _players, Board& _board);
};
#endif /* _Actor_parser */
