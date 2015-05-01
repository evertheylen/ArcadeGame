/*
 * wall.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */

#include "entity.h"

#include "life/immutable.h"
#include "physics/solid.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Wall
#define _H_Wall

class Wall: public None, public Immutable, public Solid, public SimplePrint, public Entity {
public:
	Wall(unsigned int x, unsigned y);
	void info(std::ostream& out);
};

#endif

