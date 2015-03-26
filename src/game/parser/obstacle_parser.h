/*
 * obstacle_parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "../../../lib/tinyxml/tinyxml.h"
#include "../board/obstacle.h"

#ifndef _Obstacle_parser
#define _Obstacle_parser

Obstacle parse_obstacle(TiXmlElement& elem);

#endif /* _Obstacle_parser */
