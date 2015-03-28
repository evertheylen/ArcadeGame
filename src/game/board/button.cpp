/*
 * button.cpp
 *
 *  Created on: 28 Mar 2015
 *      Author: stijn
 */

#include "button.h"
#include "gate.h"
#include "../../DesignByContract.h"

Button::Button(unsigned int x, unsigned int y, Gate* gate):
	Thing(x,y,BUTTON_WEIGHT,BUTTON_HEIGHT,BUTTON_IMPORTANCE),  // inf weight
	_gate(gate)
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of wall");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Button::Button(const Button& that):
	Thing(that),
	_gate(that._gate){
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Button& Button::operator=(const Button& that) {
	Thing::operator=(that);
	_gate = that._gate;
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::ostream& Button::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Button wasn't initialized when calling print");
	out << "Button\n";
	return out;
}

char Button::to_char() {
	REQUIRE(properlyInitialized(), "Button wasn't initialized when calling print");
	return '.';
}


void Button::onEnter(MovableThing* other) {
	_gate->set_height(0);
}

void Button::onLeave(MovableThing* other) {
	_gate->set_height(Gate::GATE_HEIGHT);
}



