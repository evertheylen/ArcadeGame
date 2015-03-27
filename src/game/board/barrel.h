#include "movable_thing.h"

#ifndef _Barrel
#define _Barrel

class Barrel: public Movable_thing {
public:
	Barrel(unsigned int x, unsigned int y);
	/**< REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of barrel");
 		ENSURE(properlyInitialized(), "constructor must end...");*/

	//! copy constructor
	Barrel(const Barrel& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Barrel& operator=(const Barrel& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	std::ostream& print(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling print");*/
	
	char to_char();
	/**< REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling to_char");*/
};


#endif // _Barrel
