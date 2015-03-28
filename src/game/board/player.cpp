#include "player.h"
#include "../../DesignByContract.h"
#include <iostream>

//TODO finish copy ctor, assign

// copy constructor
Player::Player(const Player& that):
	LivingThing(that),
	_name(that._name) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Player& Player::operator=(const Player& that) {
	LivingThing::operator=(that);
	_name = that._name;
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

Player::Player(std::string name, unsigned int x, unsigned int y):
	LivingThing(x, y, PLAYER_WEIGHT, PLAYER_HEIGHT, PLAYER_IMPORTANCE, PLAYER_MAXIMUM_WEIGHT),
	_name(name)
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

std::ostream& Player::print(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling print");
	out << "Speler " << get_name() << " bevindt zich in dit speelveld op positie (" << get_x() << "," << get_y() << ").";
	return out;
}


char Player::to_char() {
	REQUIRE(properlyInitialized(), "Player wasn't initialized when calling to_char");
	return 'Y';
}

void Player::onEnter(MovableThing* other) {
	std::cout << "player entered by " << other->to_char() << "\n";
}

void Player::onLeave(MovableThing* other) {
	std::cout << "player left by " << other->to_char() << "\n";
}

void Player::end_game() {
	std::cout << "Game should end!\n"; // TODO end the game
}

