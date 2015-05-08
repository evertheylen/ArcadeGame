/*
 * goal.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "goal.h"
#include "constants.h"

Goal::Goal(unsigned int x, unsigned y):
		SimplePrint(GOAL_SYMBOL), Entity(x, y) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}

void Goal::info(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Goal wasn't initialized when calling info");
	out << "Er bevindt zich een doel op positie (" << x << "," << y << ").\n";
}

void Goal::save(std::ostream& out, int x, int y) {
	REQUIRE(properlyInitialized(), "Goal wasn't initialized when calling save");
	out << "<DOEL beweegbaar=\"false\" x=\"" << x << "\" y=\"" << y << "\"/>";
}
