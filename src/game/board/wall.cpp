#include "wall.h"
#include "../../DesignByContract.h"

Wall::Wall(unsigned int x, unsigned int y):
	Obstacle(x,y,-1)  // inf weight
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of wall");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Wall::Wall(const Wall& that):
	Obstacle(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Wall& Wall::operator=(const Wall& that) {
	Obstacle::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::ostream& Wall::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling print");
	return out;
}

char Wall::to_char() {
	REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling print");
	return 'X';
}
