#include "monster.h"
#include "../../DesignByContract.h"
#include <iostream>

//TODO finish copy ctor, assign

// copy constructor
Monster::Monster(const Monster& that):
	LivingThing(that),
	_name(that._name) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Monster& Monster::operator=(const Monster& that) {
	LivingThing::operator=(that);
	_name = that._name;
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

Monster::Monster(std::string name, unsigned int x, unsigned int y):
	LivingThing(x, y, MONSTER_WEIGHT, MONSTER_HEIGHT, MONSTER_IMPORTANCE, MONSTER_MAXIMUM_WEIGHT),
	_name(name)
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments for constructor of player.");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

const std::string& Monster::get_name() const {
	REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling get_name");
	const std::string& result = _name;
	return result;
}

void Monster::set_name(const std::string& name) {
	REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling set_name");
	_name = name;
	ENSURE(get_name() == name, "name wasn't correctly set!");
}

std::ostream& Monster::print(std::ostream& out) {
	REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling print");
	out << "Speler " << get_name() << " bevindt zich in dit speelveld op positie (" << get_x() << "," << get_y() << ").";
	return out;
}

char Monster::to_char() {
	REQUIRE(properlyInitialized(), "Monster wasn't initialized when calling to_char");
	return 'Y';
}

void Monster::onEnter(MovableThing* other) {
	std::cout << "Monster entered by " << other->to_char() << "\n";
}

void Monster::onLeave(MovableThing* other) {
	std::cout << "Monster left by " << other->to_char() << "\n";
}
