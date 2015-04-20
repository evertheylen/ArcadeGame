/*
 * monster.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "monster.h"

Monster::Monster(unsigned int x, unsigned y):
		SimplePhysics(0, 500, x, y), Alive(1), LifePrinter('@', '0') {}


