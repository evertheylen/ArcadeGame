/*
 * gate.cpp
 *
 *  Created on: 28 Mar 2015
 *      Author: stijn
 */

#include "gate.h"
#include "../../DesignByContract.h"

Gate::Gate(unsigned int x, unsigned int y):
	Thing(x,y,GATE_WEIGHT, GATE_HEIGHT,GATE_IMPORTANCE)  // inf weight
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of wall");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Gate::Gate(const Gate& that):
	Thing(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Gate& Gate::operator=(const Gate& that) {
	Thing::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::ostream& Gate::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling print");
	out << "Gate\n";
	return out;
}

char Gate::to_char() {
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling print");
	return '.';
}

void Gate::set_height(int height) {
	_height = height;
}




