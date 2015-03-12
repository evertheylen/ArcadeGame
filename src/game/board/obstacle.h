#include "thing.h"
#include <string>

#ifndef _Obstacle
#define _Obstacle

class Obstacle: public Thing {
public:
	Obstacle(unsigned int x, unsigned int y, int weight);
	// REQUIRE(x >= 0 && y >= 0 && weight >= -1, "Incorrect constructor parameters given for obstacle");
	// ENSURE(properlyInitialized(), "constructor must end...");

	// copy constructor
	Obstacle(const Obstacle& that);
	// ENSURE(properlyInitialized(), "Copy constructor must end...");

	// copy assignment
	Obstacle& operator=(const Obstacle& that);
	// ENSURE(properlyInitialized(), "Copy by assignment must end...");

	virtual std::ostream& print(std::ostream& out);
	// REQUIRE(properlyInitialized(), "Obstacle wasn't initialized when calling print");

	virtual char to_char();
	// REQUIRE(properlyInitialized(), "Obstacle wasn't initialized when calling to_char");
};

#endif // _Obstacle
