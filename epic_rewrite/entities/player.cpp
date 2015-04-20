/*
 * player.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "player.h"

Player::Player(unsigned int x, unsigned y):
		SimplePhysics(0, 500, x, y), Alive(1), LifePrinter('Y', '0') {}


