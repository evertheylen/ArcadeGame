/*
 * actor.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "actor.h"

Actor::Actor(unsigned int x, unsigned y, char print):
		SimplePhysics(0, 500, x, y), Alive(1), LifePrinter(print, '0') {}





