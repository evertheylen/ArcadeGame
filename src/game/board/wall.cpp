#include "wall.h"
#include "../../DesignByContract.h"

Wall::Wall(unsigned int x, unsigned int y):
	Thing(x,y,WALL_WEIGHT,WALL_HEIGHT,WALL_IMPORTANCE)  // inf weight
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of wall");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Wall::Wall(const Wall& that):
	Thing(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Wall& Wall::operator=(const Wall& that) {
	Thing::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::ostream& Wall::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling print");
	out << "Wall\n";
	return out;
}

char Wall::to_char() {
	REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling print");
	return '#';
}
