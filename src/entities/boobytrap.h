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
	Boobytrap(unsigned int x, unsigned y);
	void info(std::ostream&);
	// spec: Interactive
};

#endif

