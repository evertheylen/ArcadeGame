/*
 * monster.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "monster.h"
#include "constants.h"

Monster::Monster(unsigned int x, unsigned y, std::string _name):
		Actor(x, y, MONSTER_SYMBOL, _name) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}

void Monster::info(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling info");
	out << "Er bevindt zich een monster op positie (" << x << "," << y << ").\n";
}
