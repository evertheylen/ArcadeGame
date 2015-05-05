/*
 * gate.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "gate.h"
#include "constants.h"

Gate::Gate(unsigned int x, unsigned y, std::string _name):
		Entity(x, y), _open(false) , name(_name) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}

int Gate::get_height() {
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling get_height");
	if (_open)
		return GATE_HEIGHT_OPEN;
	else
		return GATE_HEIGHT_CLOSED;
}


int Gate::get_weight() {
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling get_weight");
	return GATE_WEIGHT;
}

char Gate::to_char() {
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling to_char");
	if (_open)
		return GATE_SYMBOL_OPEN;
	else
		return GATE_SYMBOL_CLOSED;
}

void Gate::open() {
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling open");
	_open = true;
	ENSURE(_open == true, "Gate wasn't opened when calling open");
}

void Gate::close() {
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling close");
	_open = false;
	ENSURE(_open == false, "Gate wasn't closed when calling close");
}

bool Gate::is_open() {
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling is_open");
	return _open;
}

std::string& Gate::get_name() {
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling get_name");
	return name;
}

void Gate::info(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Gate wasn't initialized when calling info");
	out << "Er bevindt zich een poort (met id " << name << ") op positie (" << x << "," << y << ").\n";
}

