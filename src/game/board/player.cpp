#include "player.h"
#include "thing.h"
#include "../../DesignByContract.h"
#include <iostream>

// copy constructor
Player::Player(const Player& that):
	Thing(that),
	_name(that._name),
	_maximum_weight(that._maximum_weight) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Player& Player::operator=(const Player& that) {
	Thing::operator=(that);
	_name = that._name;
	_maximum_weight = that._maximum_weight;
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

Player::Player(std::string name, unsigned int x, unsigned int y):
	Thing(x,y,0),
	_name(name),
	_maximum_weight(1000)  // 1 ton
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments for constructor of player.");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

const std::string& Player::get_name() const {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling get_name");
	const std::string& result = _name;
	return result;
}

void Player::set_name(const std::string& name) {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling set_name");
	_name = name;
	ENSURE(get_name() == name, "name wasn't correctly set!");
}

std::ostream& Player::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling print");
	out << "Speler " << get_name() << " bevindt zich in dit speelveld op positie (" << get_x() << "," << get_y() << ").";
	return out;
}

int Player::get_maximum_weight() {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling get_maximum_weight");
	int result = _maximum_weight;
	return result;
}

void Player::set_maximum_weight(int max) {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling set_maximum_weight");
	_maximum_weight = max;
	ENSURE(get_maximum_weight() == max, "Maximum_weight wasn't correctly set!");
}

char Player::to_char() {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling to_char");
	return '@';
}
