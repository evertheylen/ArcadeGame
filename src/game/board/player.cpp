#include "player.h"
#include "thing.h"
#include <iostream>

Player::Player(std::string name, unsigned int x, unsigned int y):
	Thing(x,y,0),
	_name(name),
	_maximum_weight(1000)  // 1 ton
	{
	_initCheck = this;
}

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

int Player::get_maximum_weight() {
	return _maximum_weight;
}

void Player::set_maximum_weight(int max) {
	_maximum_weight = max;
}

char Player::to_char() {
	return '@';
}
