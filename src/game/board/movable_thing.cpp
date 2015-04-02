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

// copy constructor
MovableThing::MovableThing(const MovableThing& that):
	_solid(that._solid),
	Thing(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}


// copy assignment
MovableThing& MovableThing::operator=(const MovableThing& that) {
	_solid = that._solid;
	Thing::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

char MovableThing::to_char() {
	return 'M';
}

bool MovableThing::is_solid() {
	// TODO contract zever
	return _solid;
}

void MovableThing::end_game() {
	// do nothing
}
