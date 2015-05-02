/*
 * player.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "actor.h"
#include <string>

#ifndef _H_Player
#define _H_Player

class Player: public Actor {
public:

	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Player(unsigned int x, unsigned y, std::string _name);

	/**REQUIRE(properlyInitialized(), "Player wasn't initialized when calling info")*/
	void info(std::ostream& out);
};

#endif
