#include "obstacle.h"
#include "../../DesignByContract.h"

Obstacle::Obstacle(unsigned int x, unsigned int y, int weight):
	Thing(x,y,weight)
	{
	REQUIRE(x >= 0 && y >= 0, "Incorrect constructor parameters given for obstacle");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
}

// copy constructor
Obstacle::Obstacle(const Obstacle& that):
	Thing(that) {
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy constructor must end...");
}

// copy assignment
Obstacle& Obstacle::operator=(const Obstacle& that) {
	Thing::operator=(that);
	_initCheck = this;
	ENSURE(properlyInitialized(), "Copy by assignment must end...");
	return *this;
}

std::ostream& Obstacle::print(std::ostream& out){
	REQUIRE(properlyInitialized(), "Obstacle wasn't initialized when calling print");
	out << "Obstacle" << std::endl;
	return out;
}

char Obstacle::to_char() {
	REQUIRE(properlyInitialized(), "Obstacle wasn't initialized when calling to_char");
	return 'O';
}
