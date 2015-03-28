#include "barrel.h"
#include "../../DesignByContract.h"

Barrel::Barrel(unsigned int x, unsigned int y):
	MovableThing(x, y, BARREL_WEIGHT, BARREL_HEIGHT, BARREL_SOLIDNESS, BARREL_IMPORTANCE)
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of barrel");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Barrel::Barrel(const Barrel& that):
	MovableThing(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Barrel& Barrel::operator=(const Barrel& that) {
	MovableThing::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::ostream& Barrel::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling print");
	out << "Er bevindt zich een ton op positie (" << get_x() << "," << get_y() << ").";
	return out;
}

char Barrel::to_char() {
	REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling to_char");
	return 'O';
}
