#include "thing.h"
#include "life.h"

#include "movable_thing.h"

#ifndef _Boobytrap
#define _Boobytrap

class Boobytrap: public Thing, public Life {
public:
	static const int BOOBYTRAP_WEIGHT = 10000;
	static const int BOOBYTRAP_HEIGHT = 0;
	static const int BOOBYTRAP_IMPORTANCE = -1;  // invisible
	
	
	//! copy constructor
	Boobytrap(const Boobytrap& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Boobytrap& operator=(const Boobytrap& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	Boobytrap(unsigned int x, unsigned int y);
	/**< REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of Boobytrap");
		ENSURE(properlyInitialized(), "constructor must end...");*/

	std::ostream& print(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Boobytrap wasn't initialized when calling print");*/

	char to_char();
	/**< REQUIRE(properlyInitialized(), "Boobytrap wasn't initialized when calling to_char");*/
	
	void onEnter(MovableThing* other);
};


#endif // _Boobytrap
