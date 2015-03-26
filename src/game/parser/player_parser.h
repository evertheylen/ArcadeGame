/*
 * player_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../board/player.h"

#ifndef _Player_parser
#define _Player_parser

Player parse_player(TiXmlElement& elem);

#endif /* _Player_parser */
