/*
 * wall.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "wall.h"
#include "constants.h"

Wall::Wall(unsigned int x, unsigned y):
		Solid(WALL_HEIGHT, WALL_WEIGHT), Entity(x, y), SimplePrint(WALL_SYMBOL) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}

void Wall::info(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling info");
}

void Wall::save(std::ostream& out, int x, int y) {
	REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling save");
	out << "<MUUR beweegbaar=\"false\" x=\"" << x << "\" y=\"" << y << "\"/>";
}
