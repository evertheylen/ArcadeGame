/*
 * button.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "button.h"

Button::Button(unsigned int x, unsigned y, Gate* _gate):
		SimplePrint('.'), gate(_gate), Entity(x, y) {}


