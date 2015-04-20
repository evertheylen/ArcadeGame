/*
 * gate.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "gate.h"

Gate::Gate(unsigned int x, unsigned y):
		Entity(x, y), open(false) {}

int Gate::get_height() {
	if (open)
		return 0;
	else
		return 100;
}


int Gate::get_weight() {
	return 500;
}

char Gate::to_char() {
	if (open)
		return 0;
	else
		return '=';
}
