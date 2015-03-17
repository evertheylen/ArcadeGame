#include "barrel.h"
#include "../../DesignByContract.h"

Barrel::Barrel(unsigned int x, unsigned int y):
	Obstacle(x,y,1000)
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of barrel");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Barrel::Barrel(const Barrel& that):
	Obstacle(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Barrel& Barrel::operator=(const Barrel& that) {
	Obstacle::operator=(that);
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
	return 'o';
}
