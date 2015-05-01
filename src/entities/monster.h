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
	Monster(unsigned int x, unsigned y, std::string _name);

	void info(std::ostream& out);
};

#endif
