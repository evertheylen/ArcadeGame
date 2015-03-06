#include "player.h"
#include "thing.h"
#include <iostream>

Player::Player(std::string name, unsigned int x, unsigned int y):
	Thing(x,y,true),
	_name(name) {}

const std::string& Player::get_name() const {
	return _name;
}

void Player::set_name(const std::string& name) {
	_name = name;
}

std::ostream& Player::print(std::ostream& out){
	out << "Speler " << _name << " bevindt zich in dit speelveld op positie ";
	return out;
}

char Player::to_char() {
	return '@';
}
