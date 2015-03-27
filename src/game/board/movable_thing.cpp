/*
 * movable_thing.cpp
 *
 *  Created on: 27 Mar 2015
 *      Author: stijn
 */

#include "movable_thing.h"
#include "../../DesignByContract.h"


Movable_thing::Movable_thing(unsigned int x, unsigned int y, int weight)//:
	//_x(x), _y(y), _weight(weight)
	{
	_x = x;
	_y = y;
	_weight = weight;
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}



