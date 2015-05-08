/*
 * player.cpp
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "player.h"
#include "constants.h"

Player::Player(unsigned int x, unsigned y, std::string _name, int life):
		Actor(x, y, PLAYER_SYMBOL,_name, life) {
	ENSURE(properlyInitialized(), "Constructor must end...");
}

void Player::info(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling info");
	out << "Speler " << get_name() << " bevindt zich in dit speelveld op positie (" << x << "," << y << ").\n";
}

void Player::save(std::ostream& out, int x, int y) {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling save");
	out << "<SPELER x=\"" << x << "\" y=\"" << y << "\" lives=\"" << get_lives() << "\">\n";
	out << "\t\t<NAAM> " << get_name() << " </NAAM>\n\t</SPELER>";
}
