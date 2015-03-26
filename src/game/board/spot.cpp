/*
 * spot.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "spot.h"
#include "../../DesignByContract.h"

Spot::Spot(unsigned int x, unsigned int y): _x(x), _y(y) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Constructor must end...");
}

// copy constructor
Spot::Spot(const Spot& that):
	_x(that._x),
	_y(that._y) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Spot& Spot::operator=(const Spot& that) {
	_x = that._x;
	_y = that._y;
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

unsigned int Spot::get_x() {
	unsigned int result = _x;
	return result;
}

unsigned int Spot::get_y() {
	unsigned int result = _y;
	return result;
}

void Spot::add_stuff(Thing* thing) {
	_stuff.push_back(thing);
}

bool Spot::properlyInitialized() {
	return _initCheck == this;
}


