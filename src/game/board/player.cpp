#include "player.h"
#include "thing.h"

Player::Player(std::string name, unsigned int x, unsigned int y):
	Thing(x,y,true),
	_name(name) {}

const std::string& Player::get_name() const {
	return _name;
}

void Player::set_name(const std::string& name) {
	_name = name;
}
