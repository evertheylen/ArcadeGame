/*
 * goal.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "entity.h"

#include "life/immutable.h"
#include "physics/small.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Goal
#define _H_Goal

class Goal: public Immutable, public Small, public SimplePrint, public Entity {
public:

	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Goal(unsigned int x, unsigned y);

	/**REQUIRE(properlyInitialized(), "Goal wasn't initialized when calling info")*/
	void info(std::ostream& out);

	/**REQUIRE(properlyInitialized(), "Goal wasn't initialized when calling save")*/
	void save(std::ostream& out, int x, int y);
};

#endif
