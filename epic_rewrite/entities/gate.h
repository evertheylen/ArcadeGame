/*
 * gate.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "entity.h"

#include "life/immutable.h"
#include "physics/small.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Gate
#define _H_Gate

class Gate: public None, public Immutable, public Small, public SimplePrint, public Entity {
public:
	Gate();		//TODO PHYSICS EN PRINTER AANPASSEN ZODAT ZE CORRECT WERKEN!
};

#endif
