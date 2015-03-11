#include "obstacle.h"

#ifndef _Barrel
#define _Barrel

class Barrel: public Obstacle {
public:
	Barrel(unsigned int x, unsigned int y);
	// REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of barrel");
	// ENSURE(properlyInitialized(), "constructor must end...");

	std::ostream& print(std::ostream& out);
	// REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling print");
	
	char to_char();
	// REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling to_char");
};


#endif // _Barrel
