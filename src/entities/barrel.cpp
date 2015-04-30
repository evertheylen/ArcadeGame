/*
 * barrel.cpp

 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "barrel.h"
#include "constants.h"

Barrel::Barrel(unsigned int x, unsigned y):
		Solid(BARREL_HEIGHT, BARREL_WEIGHT), Entity(x, y), SimplePrint(BARREL_SYMBOL) {}




