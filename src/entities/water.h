
#include "entity.h"

#include "life/immutable.h"
#include "physics/solid.h"
#include "printer/simpleprint.h"
#include "ia/lethal.h"

#ifndef _H_Water
#define _H_Water

class Water: public Lethal, public Immutable, public Entity {
public:

	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Water(unsigned int x, unsigned y);
	
	/**REQUIRE(properlyInitialized(), "Water wasn't initialized when calling is_filled")*/
	bool is_filled();
	
	// spec: Printer
	/**REQUIRE(properlyInitialized(), "Water wasn't initialized when calling to_char")*/
	char to_char();
	
	// spec: Physics
	/**REQUIRE(properlyInitialized(), "Water wasn't initialized when calling get_weight")*/
	int get_weight();

	/**REQUIRE(properlyInitialized(), "Water wasn't initialized when calling get_height")*/
	int get_height();
	
	/**REQUIRE(properlyInitialized(), "Water wasn't initialized when calling info")*/
	void info(std::ostream& out);

	/**REQUIRE(properlyInitialized(), "Water wasn't initialized when calling save")*/
	void save(std::ostream& out, int x, int y);

	// Has to be both getted and setted, so easier to maintain as a public variable
	Entity* contained;
	
	virtual ~Water(); // deletes contained
};

#endif
