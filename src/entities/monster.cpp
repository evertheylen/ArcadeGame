/*
 * monster.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "monster.h"
#include "constants.h"

Monster::Monster(unsigned int x, unsigned y, std::string _name):
		Actor(x, y, MONSTER_SYMBOL, _name) {}

void Monster::info(std::ostream& out) {
	out << "Er bevindt zich een monster op positie (" << x << "," << y << ").\n";
}
