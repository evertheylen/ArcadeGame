#include "obstacle.h"

#ifndef _Wall
#define _Wall

class Wall: public Obstacle {
public:
	//! copy constructor
	Wall(const Wall& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Wall& operator=(const Wall& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	Wall(unsigned int x, unsigned int y);
	/**< REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of wall");
		ENSURE(properlyInitialized(), "constructor must end...");*/

	std::ostream& print(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling print");*/

	char to_char();
	/**< REQUIRE(properlyInitialized(), "Wall wasn't initialized when calling to_char");*/
};


#endif // _Wall
