/*
 * actor.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "actor.h"
#include "constants.h"

Actor::Actor(unsigned int x, unsigned y, char print, std::string _name, int life):
		Solid(ACTOR_HEIGHT, ACTOR_WEIGHT), Entity(x, y), Alive(life), LifePrinter(print, 0), name(_name) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}


std::string& Actor::get_name() {
	REQUIRE(properlyInitialized(), "Actor wasn't initialized when calling get_name");
	return name;
}

