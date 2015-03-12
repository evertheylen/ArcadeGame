#include "barrel.h"
#include "../../DesignByContract.h"

Barrel::Barrel(unsigned int x, unsigned int y):
	Obstacle(x,y,1000)
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of barrel");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

std::ostream& Barrel::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling print");
	out << "Er bevindt zich een ton op positie ";
	return out;
}

char Barrel::to_char() {
	REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling to_char");
	return 'o';
}
