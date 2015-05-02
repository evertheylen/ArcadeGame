/*
 * button.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "button.h"
#include "constants.h"

Button::Button(unsigned int x, unsigned y, Gate* _gate):
		SimplePrint(BUTTON_SYMBOL), gate(_gate), Entity(x, y) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}

void Button::info(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Button wasn't initialized when calling info");
	out << "Er bevindt zich een knop (gelinkt aan poort " << gate->get_name() << ") op positie (" << x << "," << y << ").\n";
}
