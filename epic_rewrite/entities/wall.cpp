/*
 * wall.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "wall.h"

Wall::Wall(unsigned int x, unsigned y):
		SimplePhysics(200, 10000, x, y), SimplePrint('#') {}


