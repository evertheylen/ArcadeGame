#include "player.h"
#include "thing.h"
#include "../../DesignByContract.h"
#include <iostream>

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
	ENSURE(result == _name, "Name was not returned correctly");
	return result;
}

void Player::set_name(const std::string& name) {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling set_name");
	_name = name;
	ENSURE(_name == name && name != "", "If you name your player "" you will get in trouble mate");
}

std::ostream& Player::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling print");
	out << "Speler " << _name << " bevindt zich in dit speelveld op positie ";
	return out;
}

int Player::get_maximum_weight() {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling get_maximum_weight");
	int result = _maximum_weight;
	ENSURE(result == _maximum_weight, "Maximum_weight returned incorrectly");
	return result;
}

void Player::set_maximum_weight(int max) {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling set_maximum_weight");
	_maximum_weight = max;
	ENSURE(_maximum_weight == max, "Maximum_weight wasn't correctly set!");
}

char Player::to_char() {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling to_char");
	return '@';
}
