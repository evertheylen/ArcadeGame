/*
 * monster.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "monster.h"
#include "constants.h"

Monster::Monster(unsigned int x, unsigned y, std::string _name, int life):
		Actor(x, y, MONSTER_SYMBOL, _name, life) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}

void Monster::info(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling info");
	out << "Er bevindt zich een monster op positie (" << x << "," << y << ").\n";
}

void Monster::save(std::ostream& out, int x, int y) {
	REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling save");
	out << "<MONSTER x=\"" << x << "\" y=\"" << y << "\" lives=\"" << get_lives() << "\">\n";
	out << "\t\t<ID> " << get_name() << " </ID>\n\t</MONSTER>";
}
