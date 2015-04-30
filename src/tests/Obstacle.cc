#include "thing.h"
#include "barrel.h"
#include "movable_thing.h"

#ifndef _Water
#define _Water

class Water: public Thing {
public:
	static const int WATER_WEIGHT = 500;
	static const int WATER_HEIGHT = - Barrel::BARREL_HEIGHT; // -100
	static const int WATER_IMPORTANCE = 900;
	
	
	//! copy constructor
	Water(const Water& that);
	/**< ENSURE(properlyInitialized(), "Copy constructor must end...");*/

	//! copy assignment
	Water& operator=(const Water& that);
	/**< ENSURE(properlyInitialized(), "Copy by assignment must end...");*/

	Water(unsigned int x, unsigned int y);
	/**< REQUIRE(x >= 0 && y >= 0, "Incorrect arguments specified for constructor of Water");
		ENSURE(properlyInitialized(), "constructor must end...");*/

	std::ostream& print(std::ostream& out);
	/**< REQUIRE(properlyInitialized(), "Water wasn't initialized when calling print");*/

	char to_char();
	/**< REQUIRE(properlyInitialized(), "Water wasn't initialized when calling to_char");*/
	
	int get_importance() const;
	
	void onEnter(MovableThing* other);
	
private:
	bool _filled;
};


#endif // _Water
