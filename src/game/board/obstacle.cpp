#include "obstacle.h"
#include "../../DesignByContract.h"

Obstacle::Obstacle(unsigned int x, unsigned int y, int weight):
	Thing(x,y,weight)
	{
	REQUIRE(x >= 0 && y >= 0 && weight >= -1, "Incorrect constructor parameters given for obstacle");
	_initCheck = this;
	ENSURE(properlyInitialized(), "constructor must end...");
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
