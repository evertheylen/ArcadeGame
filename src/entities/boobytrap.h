/*
 * boobytrap.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "entity.h"

#include "life/alive.h"
#include "physics/small.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Boobytrap
#define _H_Boobytrap

class Boobytrap: public Alive, public Small, public SimplePrint, public Entity {
public:

	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Boobytrap(unsigned int x, unsigned y);

	/**REQUIRE(properlyInitialized(), "Boobytrap wasn't initialized when calling info")*/
	void info(std::ostream&);

	/**REQUIRE(properlyInitialized(), "Boobytrap wasn't initialized when calling save")*/
	void save(std::ostream& out, int x, int y);
};

#endif

