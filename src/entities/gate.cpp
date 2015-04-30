/*
 * gate.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "gate.h"
#include "constants.h"

Gate::Gate(unsigned int x, unsigned y):
		Entity(x, y), _open(false) {}

int Gate::get_height() {
	if (_open)
		return GATE_HEIGHT_OPEN;
	else
		return GATE_HEIGHT_CLOSED;
}


int Gate::get_weight() {
	return GATE_WEIGHT;
}

char Gate::to_char() {
	if (_open)
		return GATE_SYMBOL_OPEN;
	else
		return GATE_SYMBOL_CLOSED;
}

void Gate::open() {
	_open = true;
}

void Gate::close() {
	_open = false;
}

bool Gate::is_open() {
	return _open;
}

