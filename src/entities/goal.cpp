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
