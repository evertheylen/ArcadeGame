/*
 * actor.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "actor.h"
#include "constants.h"

Actor::Actor(unsigned int x, unsigned y, char print, std::string _name):
		Solid(ACTOR_HEIGHT, ACTOR_WEIGHT), Entity(x, y), Alive(ACTOR_LIVES), LifePrinter(print, 0), name(_name) {}


std::string Actor::get_name() {
	return name;
}
