/*
 * alive.cpp
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "alive.h"

Alive::Alive(int lives) {
	_lives = lives;
}

bool Alive::is_alive() {
	return _lives > 0;
}

void Alive::kill() {
	_lives--;
}


