/*
 * barrel.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */


#include "entity.h"

#include "life/immutable.h"
#include "physics/solid.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Barrel
#define _H_Barrel

class Barrel: public None, public Immutable, public Solid, public SimplePrint, public Entity {
public:

	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Barrel(unsigned int x, unsigned int y);

	/**REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling info")*/
	void info(std::ostream& out);

	/**REQUIRE(properlyInitialized(), "Barrel wasn't initialized when calling save")*/
	void save(std::ostream& out, int x, int y);
};

#endif
