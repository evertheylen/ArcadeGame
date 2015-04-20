/*
 * actor.h
 *
 *  Created on: 20 Apr 2015
 *      Author: stijn
 */

#include "ia/none.h"
#include "life/alive.h"
#include "physics/simplephysics.h"
#include "printer/lifeprinter.h"
#include "entity.h"

#ifndef _H_Actor
#define _H_Actor

// If you don't like multiple inheritance, you should stop reading right now and find some other
// project you like. I'm serious. Also, if you don't like virtuals or RTTI in general, consider
// rm -rf'ing your local copy of this project, and then watching some cat gifs.

// If you _do_ like MI and RTTI, buckle up, this is going to be quite a ride.

class Actor: public None, public Alive, public SimplePhysics, public LifePrinter, public Entity {
public:
	Actor(unsigned int x, unsigned y, char print);
};

#endif
