/*
 * player.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "player.h"
#include "constants.h"

Player::Player(unsigned int x, unsigned y, std::string _name):
		Actor(x, y, PLAYER_SYMBOL,_name) {}

void Player::info(std::ostream& out) {
	out << "Speler " << get_name() << " bevindt zich in dit speelveld op positie (" << x << "," << y << ").\n";
}
