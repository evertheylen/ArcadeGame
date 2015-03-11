#include "wall.h"
#include "../../DesignByContract.h"

Wall::Wall(unsigned int x, unsigned int y):
	Obstacle(x,y,-1)  // inf weight
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of wall");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

std::ostream& Wall::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling print");
	return out;
}

char Wall::to_char() {
	REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling print");
	return 'X';
}
