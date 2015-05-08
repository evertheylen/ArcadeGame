/*
 * actor.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include <string>

#include "ia/none.h"
#include "life/alive.h"
#include "physics/solid.h"
#include "printer/lifeprinter.h"
#include "entity.h"

#ifndef _H_Actor
#define _H_Actor


class Actor: public None, public Alive, public Solid, public LifePrinter, public Entity {
public:

	/**ENSURE(properlyInitialized(), "Constructor must end...")*/
	Actor(unsigned int x, unsigned y, char print, std::string _name, int life);
	
	/**REQUIRE(properlyInitialized(), "Actor wasn't initialized when calling get_name")*/
	std::string& get_name();
	
private:
	std::string name;
};

#endif
