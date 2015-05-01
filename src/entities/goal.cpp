/*
 * goal.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "goal.h"
#include "constants.h"

Goal::Goal(unsigned int x, unsigned y):
		SimplePrint(GOAL_SYMBOL), Entity(x, y) {}

void Goal::info(std::ostream& out) {
	out << "Er bevindt zich een doel op positie (" << x << "," << y << ").\n";
}
