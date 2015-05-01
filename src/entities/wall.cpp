/*
 * wall.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "wall.h"
#include "constants.h"

Wall::Wall(unsigned int x, unsigned y):
		Solid(WALL_HEIGHT, WALL_WEIGHT), Entity(x, y), SimplePrint(WALL_SYMBOL) {}

void Wall::info(std::ostream& out) {}
