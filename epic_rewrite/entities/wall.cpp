/*
 * wall.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "wall.h"

Wall::Wall(unsigned int x, unsigned y):
		Solid(200, 10000), Entity(x, y), SimplePrint('#') {}


