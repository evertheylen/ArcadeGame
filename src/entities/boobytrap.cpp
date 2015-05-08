/*
 * boobytrap.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "boobytrap.h"
#include "constants.h"

Boobytrap::Boobytrap(unsigned int x, unsigned y):
		Alive(BOOBYTRAP_LIVES), SimplePrint(BOOBYTRAP_SYMBOL), Entity(x, y) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}

void Boobytrap::info(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Boobytrap wasn't initialized when calling info");
	out << "Er bevindt zich een valstrik op positie (" << x << "," << y << ").\n";
}

void Boobytrap::save(std::ostream& out, int x, int y) {
	REQUIRE(properlyInitialized(), "Boobytrap wasn't initialized when calling save");
	out << "<VALSTRIK beweegbaar=\"false\" x=\"" << x << "\" y=\"" << y << "\"/>";
}
