/*
 * actor.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "actor.h"

Actor::Actor(unsigned int x, unsigned y, char print, std::string _name):
		Solid(0, 500), Entity(x, y), Alive(1), LifePrinter(print, 0), name(_name) {}





