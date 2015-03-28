#include "thing.h"
#include "movable_thing.h"

#ifndef _Goal
#define _Goal

class Goal: public Thing {
public:
	static const int GOAL_WEIGHT = 10000;
	static const int GOAL_HEIGHT = 200;
	static const int GOAL_IMPORTANCE = 1500;
	
	
	//! copy constructor
	Goal(const Goal& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Goal& operator=(const Goal& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	Goal(unsigned int x, unsigned int y);
	/**< REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of Goal");
		ENSURE(properlyInitialized(), "constructor must end...");*/

	std::ostream& print(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Goal wasn't initialized when calling print");*/

	char to_char();
	/**< REQUIRE(properlyInitialized(), "Goal wasn't initialized when calling to_char");*/
	
	void onEnter(MovableThing* other);
};


#endif // _Goal
