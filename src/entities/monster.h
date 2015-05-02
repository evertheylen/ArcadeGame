/*
 * monster.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "actor.h"

#include <string>

#ifndef _H_Monster
#define _H_Monster

class Monster: public Actor {
public:

	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Monster(unsigned int x, unsigned y, std::string _name);

	/**REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling info")*/
	void info(std::ostream& out);
};

#endif
