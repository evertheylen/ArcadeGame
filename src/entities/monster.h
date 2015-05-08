/*
 * monster.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "actor.h"
#include "constants.h"
#include <string>

#ifndef _H_Monster
#define _H_Monster

class Monster: public Actor {
public:

	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Monster(unsigned int x, unsigned y, std::string _name, int life = ACTOR_LIVES);

	/**REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling info")*/
	void info(std::ostream& out);

	/**REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling save")*/
	void save(std::ostream& out, int x, int y);
};

#endif
