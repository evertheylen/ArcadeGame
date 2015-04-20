/*
 * barrel.h
 *
 *  Created on: 19 Apr 2015
 *      Author: stijn
 */


#include "entity.h"

#include "life/immutable.h"
#include "physics/simplephysics.h"
#include "printer/simpleprint.h"
#include "ia/none.h"

#ifndef _H_Barrel
#define _H_Barrel

class Barrel: public None, public Immutable, public SimplePhysics, public SimplePrint, public Entity {
public:
	Barrel(unsigned int x, unsigned int y);
};

#endif
