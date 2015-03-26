/*
 * movement_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../movement/movement.h"
#include "parser.h"

#ifndef _Movement_parser
#define _Movement_parser

class Movement_parser: public Parser {
public:
	Movement parse_movement(TiXmlElement& move_elem);
};

#endif /* _Movement_parser */
