/*
 * movement_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../actions/actions.h"
#include "parser.h"
#include "../game.h"

#include <list>

#ifndef _Action_parser
#define _Action_parser

class Action_parser: public Parser {
public:
	Action_parser(std::ostream* stream, std::string filename);
	
	Action_parser() = default;

	std::list<Action>* parse_action(TiXmlElement* move_elem, Game::Playermap& _players);
};

#endif /* _Movement_parser */
