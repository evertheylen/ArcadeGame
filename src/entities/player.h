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
	Player(unsigned int x, unsigned y, std::string _name);

	void info(std::ostream& out);
};

#endif
