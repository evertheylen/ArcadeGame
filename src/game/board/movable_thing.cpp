/*
 * movable_thing.cpp
 *
 *  Created on: 27 Mar 2015
 *      Author: stijn & evert
 */

#include "movable_thing.h"
#include "../../DesignByContract.h"


MovableThing::MovableThing(unsigned int x, unsigned int y, int weight, int height, int importance, bool solid):
	Thing(x, y, weight, height, importance),  _solid(solid)
	{
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// TODO copy ctor, copy assign

char MovableThing::to_char() {
	return 'M';
}

bool MovableThing::is_solid() {
	// TODO contract zever
	return _solid;
}
